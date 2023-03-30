
#define WATCH_BUFFER_SIZE 8192
typedef struct WatchedDirectoryWin32 WatchedDirectoryWin32;
struct WatchedDirectoryWin32 {
	HANDLE file_handle;
	FILETIME time;
};

bool platform_file_read_all(const char* path, void** data_out, uintptr_t* size_out) {
	FILE* f;
	if (fopen_s(&f, path, "rb")) {
		return false;
	}

	fseek(f, 0, SEEK_END);
	long file_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	void* data = malloc(file_size);
	long read_size = fread(data, 1, file_size, f);
	if (read_size != file_size) {
		fclose(f);
		return false;
	}

	*data_out = data;
	*size_out = file_size;
	fclose(f);
	return true;
}

bool platform_file_exists(const char* path) {
	DWORD dwAttrib = GetFileAttributesA(path);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void platform_open_console(void) {
}

WatchedFile* platform_watch_file(const char* path) {
	WatchedDirectoryWin32* w = malloc(sizeof(WatchedDirectoryWin32));
	w->file_handle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	GetFileTime(w->file_handle, NULL, NULL, &w->time);
	return (WatchedFile*)w;
}

bool platform_watch_file_check_if_changed(WatchedFile* handle) {
	WatchedDirectoryWin32* w = (WatchedDirectoryWin32*)handle;

	FILETIME new_time;
	GetFileTime(w->file_handle, NULL, NULL, &new_time);

	bool has_changed = w->time.dwLowDateTime != new_time.dwLowDateTime || w->time.dwHighDateTime != new_time.dwHighDateTime;

	w->time = new_time;

	return has_changed;
}
