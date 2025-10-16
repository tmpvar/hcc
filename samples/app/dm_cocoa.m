#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

// Custom window delegate to handle events
@interface HCCWindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic) BOOL shouldClose;
@property (nonatomic) BOOL wasResized;
@property (nonatomic) uint32_t newWidth;
@property (nonatomic) uint32_t newHeight;
@end

@implementation HCCWindowDelegate
- (instancetype)init {
	self = [super init];
	if (self) {
		_shouldClose = NO;
		_wasResized = NO;
		_newWidth = 0;
		_newHeight = 0;
	}
	return self;
}

- (void)windowWillClose:(NSNotification *)notification {
	self.shouldClose = YES;
}

- (void)windowDidResize:(NSNotification *)notification {
	NSWindow *window = [notification object];
	NSRect contentRect = [[window contentView] frame];
	self.wasResized = YES;
	self.newWidth = (uint32_t)contentRect.size.width;
	self.newHeight = (uint32_t)contentRect.size.height;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
	self.shouldClose = YES;
	return NO; // We'll handle closing manually
}
@end

// Custom view to host the Metal layer
@interface HCCMetalView : NSView
@property (nonatomic, strong) CAMetalLayer *metalLayer;
@end

@implementation HCCMetalView
- (instancetype)initWithFrame:(NSRect)frameRect {
	self = [super initWithFrame:frameRect];
	if (self) {
		// Create and configure metal layer BEFORE setting wantsLayer
		// This ensures makeBackingLayer will return our configured layer
		CGFloat scale = [[NSScreen mainScreen] backingScaleFactor];
		_metalLayer = [CAMetalLayer layer];
		_metalLayer.frame = frameRect;
		_metalLayer.contentsScale = scale;
		_metalLayer.drawableSize = CGSizeMake(frameRect.size.width * scale,
		                                       frameRect.size.height * scale);
		_metalLayer.presentsWithTransaction = NO;
		_metalLayer.opaque = YES;
		// Now set wantsLayer - this will call makeBackingLayer which returns our layer
		self.wantsLayer = YES;
	}
	return self;
}

- (CALayer *)makeBackingLayer {
	// This method is called when wantsLayer is set to YES
	// Return our pre-configured metal layer
	if (!_metalLayer) {
		// Fallback: if somehow called before initWithFrame completes
		CGFloat scale = [[NSScreen mainScreen] backingScaleFactor];
		_metalLayer = [CAMetalLayer layer];
		_metalLayer.frame = self.bounds;
		_metalLayer.contentsScale = scale;
		_metalLayer.drawableSize = CGSizeMake(self.bounds.size.width * scale,
		                                       self.bounds.size.height * scale);
		_metalLayer.presentsWithTransaction = NO;
		_metalLayer.opaque = YES;
	}
	return _metalLayer;
}

- (void)setFrameSize:(NSSize)newSize {
	[super setFrameSize:newSize];
	if (_metalLayer) {
		_metalLayer.frame = self.bounds;
		// Update drawable size for retina displays
		CGFloat scale = _metalLayer.contentsScale;
		_metalLayer.drawableSize = CGSizeMake(newSize.width * scale,
		                                       newSize.height * scale);
	}
}

- (BOOL)acceptsFirstResponder {
	return YES;
}
@end

typedef struct DmCocoa DmCocoa;
struct DmCocoa {
	NSApplication *app;
	NSWindow *window;
	HCCWindowDelegate *windowDelegate;
	HCCMetalView *metalView;
	int32_t window_width;
	int32_t window_height;
};

DmCocoa dm;

void dm_init(void) {
	@autoreleasepool {
		// Initialize NSApplication
		dm.app = [NSApplication sharedApplication];
		[dm.app setActivationPolicy:NSApplicationActivationPolicyRegular];

		// Create a simple menu bar (required for proper keyboard input)
		NSMenu *menubar = [[NSMenu alloc] init];
		NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
		[menubar addItem:appMenuItem];
		[dm.app setMainMenu:menubar];

		NSMenu *appMenu = [[NSMenu alloc] init];
		NSString *quitTitle = [@"Quit " stringByAppendingString:[[NSProcessInfo processInfo] processName]];
		NSMenuItem *quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
		                                                       action:@selector(terminate:)
		                                                keyEquivalent:@"q"];
		[appMenu addItem:quitMenuItem];
		[appMenuItem setSubmenu:appMenu];

		[dm.app finishLaunching];
		[dm.app activateIgnoringOtherApps:YES];
	}
}

void dm_screen_dims(int* width_out, int* height_out) {
	@autoreleasepool {
		NSScreen *screen = [NSScreen mainScreen];
		NSRect frame = [screen frame];
		*width_out = (int)frame.size.width;
		*height_out = (int)frame.size.height;
	}
}

DmWindow dm_window_open(int width, int height) {
	@autoreleasepool {
		DmWindow window;

		dm.window_width = width;
		dm.window_height = height;

		NSRect frame = NSMakeRect(0, 0, width, height);
		NSWindowStyleMask style = NSWindowStyleMaskTitled |
		                          NSWindowStyleMaskClosable |
		                          NSWindowStyleMaskMiniaturizable |
		                          NSWindowStyleMaskResizable;

		dm.window = [[NSWindow alloc] initWithContentRect:frame
		                                        styleMask:style
		                                          backing:NSBackingStoreBuffered
		                                            defer:NO];

		[dm.window setTitle:@"HCC Sample"];
		[dm.window center];

		// Create our custom Metal view
		dm.metalView = [[HCCMetalView alloc] initWithFrame:frame];
		[dm.window setContentView:dm.metalView];

		// Set up window delegate
		dm.windowDelegate = [[HCCWindowDelegate alloc] init];
		[dm.window setDelegate:dm.windowDelegate];

		[dm.window makeKeyAndOrderFront:nil];
		[dm.window makeFirstResponder:dm.metalView];

		// Return the Metal layer as the handle (for Vulkan surface creation)
		window.instance = (__bridge void*)dm.app;
		window.handle = (__bridge void*)dm.metalView.metalLayer;

		return window;
	}
}

bool dm_process_events(DmEvent* e) {
	@autoreleasepool {
		// Check if window was closed
		if (dm.windowDelegate.shouldClose) {
			dm.windowDelegate.shouldClose = NO;
			e->type = DM_EVENT_TYPE_WINDOW_CLOSED;
			return true;
		}

		// Check if window was resized
		if (dm.windowDelegate.wasResized) {
			dm.windowDelegate.wasResized = NO;
			if (dm.windowDelegate.newWidth != dm.window_width ||
			    dm.windowDelegate.newHeight != dm.window_height) {
				dm.window_width = dm.windowDelegate.newWidth;
				dm.window_height = dm.windowDelegate.newHeight;
				e->type = DM_EVENT_TYPE_WINDOW_RESIZED;
				e->window_width = dm.window_width;
				e->window_height = dm.window_height;
				return true;
			}
		}

		// Process events from the queue
		NSEvent *event;
		while ((event = [dm.app nextEventMatchingMask:NSEventMaskAny
		                                    untilDate:nil
		                                       inMode:NSDefaultRunLoopMode
		                                      dequeue:YES]) != nil) {

			switch ([event type]) {
				case NSEventTypeKeyDown: {
					NSString *chars = [event charactersIgnoringModifiers];
					if ([chars length] > 0) {
						unichar ch = [chars characterAtIndex:0];
						if (ch < 128) {
							e->type = DM_EVENT_TYPE_KEY_PRESSED;
							e->key = (char)ch;
							[dm.app sendEvent:event];
							return true;
						}
					}
					break;
				}

				case NSEventTypeKeyUp: {
					NSString *chars = [event charactersIgnoringModifiers];
					if ([chars length] > 0) {
						unichar ch = [chars characterAtIndex:0];
						if (ch < 128) {
							e->type = DM_EVENT_TYPE_KEY_RELEASED;
							e->key = (char)ch;
							[dm.app sendEvent:event];
							return true;
						}
					}
					break;
				}

				default:
					[dm.app sendEvent:event];
					break;
			}
		}

		return false;
	}
}
