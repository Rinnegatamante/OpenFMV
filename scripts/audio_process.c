#include <dirent.h>
#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>

void patch_dir(const char *name) {
	char fname_start[256];
	DIR *d = opendir(name);
	struct dirent *entry;
	int i = 1;
	while (entry = readdir(d)) {
		if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
			char fname[256];
			if (entry->d_type != DT_DIR) {
				char params[1024];
				strcpy(fname_start, entry->d_name);
				fname_start[4] = 0;
				printf("(%d) Patching %s\n", i++, entry->d_name);
				sprintf(fname, "oggs/%s", fname_start);
				mkdir(fname, 0777);
				sprintf(params, "-i \"AudioClip/%s\" \"oggs/%s/%s.ogg", entry->d_name, fname_start, entry->d_name);
				SHELLEXECUTEINFO ShExecInfo = {0};
				ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
				ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
				ShExecInfo.hwnd = NULL;
				ShExecInfo.lpVerb = "open";
				ShExecInfo.lpFile = "ffmpeg.exe";        
				ShExecInfo.lpParameters = params;   
				ShExecInfo.lpDirectory = NULL;
				ShExecInfo.nShow = SW_SHOW;
				ShExecInfo.hInstApp = NULL; 
				ShellExecuteEx(&ShExecInfo);
				WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
				CloseHandle(ShExecInfo.hProcess);
			}
		}
	}
	closedir(d);
}

int main() {
	mkdir("oggs", 0777);
	patch_dir("AudioClip");
	return 0;
}
