#define _CRT_SECURE_NO_WARNINGS //SDLチェック無効

#include <cstddef>
#include <limits>
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <typeinfo>
#include <exception>
#include <initializer_list>
#include <cstdalign>
#include <stdexcept>
#include <cassert>
#include <cerrno>
#include <system_error>
#include <string>

#if __has_include(<string_view>)
#   include <string_view>
#endif

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>
#include <cfenv>
#include <random>
#include <numeric>
#include <iosfwd>
#include <iostream>
#include <ios>
#include <streambuf>
#include <istream>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#if __has_include(<filesystem>)
#   include <filesystem>
#endif

#include <cstdio>
#include <cinttypes>


#include <regex>
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <future>
#include <cstring>       
#include <tuple>   
#include <ctime>
#include <chrono>

#define _USE_MATH_DEFINES //数値演算定数を定義
#include <cmath>

#define OPEN_PROCESS_TOKEN (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY) // アクセス権の定数

class str : public std::string{
    public:
        using std::string::string;
        using std::string::operator=;
        using std::string::operator+=;

        //str() = default;
        str(std::string target) : std::string(target){}

        std::string replace_all(std::string target, std::string replacement){
            std::string::size_type pos = 0;
            std::string stringText = *this;
            while ((pos = stringText.find(target, pos)) != std::string::npos) {
                stringText.replace(pos, target.length(), replacement);
                pos += replacement.length();
            }
            return stringText;
        }
        
        std::vector<std::string> split(std::string delStr) {
            int first = 0;
            std::vector<std::string> result;
            std::vector<int> subStrNum = this->find_all(delStr);
            subStrNum.push_back(this->size()); // 最後の部分文字列を処理するために文字列の末尾を追加
        
            for (int i = 0; i < subStrNum.size(); ++i) {
                std::string subStr(*this, first, subStrNum[i] - first);
                result.push_back(subStr); // 部分文字列を結果に追加
                first = subStrNum[i] + delStr.size();
            }
            return result;
        }

        std::vector<int> find_all(std::string subStr) {
            std::vector<int> result;
            std::string stringText = *this;
            int subStrSize = subStr.size();
            int pos = stringText.find(subStr);
            while (pos != std::string::npos) {
                result.push_back(pos);
                pos = stringText.find(subStr, pos + subStrSize);
            }
            return result;
        }
        std::string to_string(){
            return (std::string)*this;
        }

        str& operator+(const str &targetText) {
            str strText = targetText;
            for(auto& s : strText){
                this -> push_back(s);
            }
            return *this;
        }

        str& operator+(std::string targetText) {
            std::string strText = targetText;
            for(auto& s : strText){
                this -> push_back(s);
            }
            return *this;
        }

        str operator= (std::vector<int> targetVec){
            str result;
            for(int& v : targetVec){
                result += std::to_string(v);
            }
            return result;
        }

        str operator= (std::vector<double> targetVec){
            str result;
            for(double& v : targetVec){
                result += std::to_string(v);
            }
            return result;
        }
        
        str operator* (int n) const{
            if(n <= 1) return *this;
            str result;
            result.reserve(this->length() * n);
            for(int i = 0 ; i < n ; i++){
                result += *this;
            }
            return result;
        }
};

class vec : public std::vector<std::string>{
    public:
        using std::vector<std::string>::vector;
        using std::vector<std::string>::operator=;
        //vec() = default;
        vec(std::vector<std::string> target) : std::vector<std::string>(target){}

        std::string to_str (){
            std::string ans = "";
            std::vector<std::string> sourceVec = *this;
            for(std::string& s : sourceVec){
                ans = ans + s;
            }
            return ans;
        }
        std::vector<std::string> to_vec (){
            return (std::vector<std::string>)*this;
        }

        int vec_compare(std::vector<std::string> target){
            std::vector<std::string> targetVec = target;
            std::vector<std::string> sourceVec = *this;
            std::sort(targetVec.begin(), targetVec.end());
            std::sort(sourceVec.begin(), sourceVec.end());
            return std::equal(targetVec.begin(), targetVec.end(), sourceVec.begin(), sourceVec.end());
        }

        vec& operator= (std::vector<int> targetVec){
            this -> clear();
            for(int& v : targetVec){
                this -> push_back(std::to_string(v));
            }
            return *this;
        }

        vec& operator= (std::vector<double> targetVec){
            this -> clear();
            for(double& v : targetVec){
                this -> push_back(std::to_string(v));
            }
            return *this;
        }

        vec& operator= (vec targetVec){
            this -> clear();
            for(std::string& v : targetVec){
                this -> push_back(v);
            }
            return *this;
        }

        vec& operator+ (std::vector<int> targetVec){
            for(int& v : targetVec){
                this -> push_back(std::to_string(v));
            }
            return *this;
        }

        vec& operator+ (std::vector<double> targetVec){
            for(double& v : targetVec){
                this -> push_back(std::to_string(v));
            }
            return *this;
        }

        vec& operator+ (vec targetVec){
            for(std::string& v : targetVec){
                this -> push_back(v);
            }
            return *this;
        }

        vec& operator+ (std::vector<std::string> targetVec){
            for(std::string& v : targetVec){
                this -> push_back(v);
            }
            return *this;
        }

        void operator+= (std::vector<int> targetVec){
            for(int& v : targetVec){
                this -> push_back(std::to_string(v));
            }
        }

        void operator+= (std::vector<double> targetVec){
            for(double& v : targetVec){
                this -> push_back(std::to_string(v));
            }
        }

        void operator+= (vec targetVec){
            for(std::string& v : targetVec){
                this -> push_back(v);
            }
        }

        void operator+= (std::vector<std::string> targetVec){
            for(std::string& v : targetVec){
                this -> push_back(v);
            }
        }
};



#ifdef __linux__ 
    //linux code
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
    
    class TCP{
        protected:
            int sock;
            int bufsize;
            int maxpending; // 最大接続台数
        public:
            TCP(int bufsize = 1024, int maxpending = 5){
                this->maxpending = maxpending;
                this->bufsize = bufsize;
                this->sock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP); /* ソケットを作成 (TCP) */
                if (this->sock < 0) { 
                    perror("socket() failed");
                    this->~TCP();
                }
            }
            ~TCP(){
                close(this->sock);
            }
            int get_sock(){
                return this->sock;
            }
            void set_sock(int sock){
                this->sock = sock;
            }
            int port_connect(struct sockaddr_in *addr){ /* 接続する */
                if (connect(this->sock, (struct sockaddr *)addr, sizeof(*addr)) < 0) { 
                    perror("connect() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_send(char *msg){ /* 送信する */
                int len = strlen(msg);
                if (send(this->sock, msg, len, 0) != len) {
                    perror("send() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_bind(struct sockaddr_in *addr){ /* ポートに結びつける */
                int addrSize = sizeof(*addr);
                if (bind(this->sock, (struct sockaddr *)addr, addrSize) < 0) { 
                    perror("bind() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_listen(){
                if (listen(this->sock, this->maxpending) < 0) {
                    perror("listen() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_accept(struct sockaddr_in *caddr){
                int csock;
                unsigned int csize = sizeof(*caddr);
                csock = accept(this->sock, (struct sockaddr *)caddr, &csize);
                if (csock< 0) {
                    perror ("accept() failed");
                    return -1;
                }
                return csock;
            }
            
            int port_recv(int csock, char* buff){ /* 受信する */
                int bytes;
                bytes = recv(csock, buff, this->bufsize - 1, 0);
                if (bytes < 0) { // 空文字をエラーにしない
                    perror("recv() failed");
                    return 1;
                }
                buff[bytes] = '\0'; /* 文字列として扱うため最後を \0 で終端して表示する */ 
                return 0;
            }
    };

    class UDP{
        protected:
            int sock;
            int bufsize;
        public:
            UDP(int bufsize = 1024){
                this->bufsize = bufsize;
                this->sock = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP); /* ソケットを作成する (UDP)*/
                if (this->sock < 0) { 
                    perror("socket() failed");
                    this->~UDP();
                }
            }
            ~UDP(){
                close(this->sock);
            }
            int get_sock(){
                return this->sock;
            }
            void set_sock(int sock){
                this->sock = sock;
            }
            int port_send(struct sockaddr_in *addr, char *msg){ /* 送信 */
                int len = strlen(msg);
                int addrSize = sizeof(*addr);
                if (sendto(this->sock, msg, len, 0, (struct sockaddr *)addr, addrSize) != len){
                    perror("sendto() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_bind(struct sockaddr_in *addr){ /* ポートに結びつける */
                int addrSize = sizeof(*addr);
                if (bind(this->sock, (struct sockaddr *)addr, addrSize) < 0) { 
                    perror("bind() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_recv(struct sockaddr_in *caddr, char* buff){ /* 受信する */
                int bytes;
                unsigned int csize = sizeof(*caddr);
            
                bytes = recvfrom (this->sock, buff, this->bufsize - 1, 0, (struct sockaddr *)caddr, &csize);
                if ((bytes) < 0) { // 空文字をエラーにしない
                    perror("recvfrom() failed");
                    return 1;
                }
                buff[bytes] = '\0'; /* 文字列として扱うため最後を \0 で終端して表示する */ 
                return 0;
            }
    };

#elif _WIN32
    // windows code
    #include <direct.h>
    #include <tchar.h>
    #include <WinSock2.h>
    #include <ws2tcpip.h>
    #include <windowsx.h>
    #include <Windows.h>
    //#include <shellapi.h>
    #pragma comment(lib, "ws2_32.lib")
    #pragma warning(disable:4996)

    class TCP{
        protected:
            WSADATA wsaData;
            int sock;
            int bufsize;
            int maxpending; // 最大接続台数
        public:
            TCP(int bufsize = 1024, int maxpending = 5){
                this->bufsize = bufsize;
                this->maxpending = maxpending;
                WSAStartup(MAKEWORD(2, 0), &this->wsaData);   //MAKEWORD(2, 0) : winsock ver. 2.0
                this->sock = socket(AF_INET, SOCK_STREAM, 0);  //AF_INET : IPv4、SOCK_DGRAM : UDP SOCK_STREAM : TCP
                if (this->sock < 0) { 
                    perror("socket() failed");
                    this->~TCP();
                }
            }
            ~TCP(){
                closesocket(this->sock); 
                WSACleanup();
            }
            int get_sock(){
                return this->sock;
            }
            void set_sock(int sock){
                this->sock = sock;
            }
            int port_connect(struct sockaddr_in *addr){ /* 接続する */
                if (connect(this->sock, (struct sockaddr *)addr, sizeof(*addr)) < 0) { 
                    perror("connect() failed");
                    return 1;
                }
                return 0;
            }

            int port_send(char *msg){ /* 送信する */
                int len = strlen(msg);
                if (send(this->sock, msg, len, 0) != len) {
                    perror("send() failed");
                    return 1;
                }
                return 0;
            }

            int port_bind(struct sockaddr_in *addr){ /* ポートに結びつける */
                int addrSize = sizeof(*addr);
                if (bind(this->sock, (struct sockaddr *)addr, addrSize) < 0) { 
                    perror("bind() failed");
                    return 1;
                }
                return 0;
            }

            int port_listen(){
                if (listen(this->sock, this->maxpending) < 0) {
                    perror("listen() failed");
                    return 1;
                }
                return 0;
            }

            int port_accept(struct sockaddr_in *caddr){
                int csock;
                int csize = sizeof(*caddr);
                csock = accept(this->sock, (struct sockaddr *)caddr, &csize);
                if (csock< 0) {
                    perror ("accept() failed");
                    return -1;
                }
                return csock;
            }

            int port_recv(int csock, char* buff){ /* 受信する */
                int bytes;
                bytes = recv(csock, buff, this->bufsize - 1, 0);
                if (bytes < 0) { // 空文字をエラーにしない
                    perror("recv() failed");
                    return 1;
                }
                buff[bytes] = '\0'; /* 文字列として扱うため最後を \0 で終端して表示する */ 
                return 0;
            }

    };

    class UDP{
        protected:
            WSADATA wsaData;
            int sock;
            int bufsize;
        public:
            UDP(int bufsize = 1024){
                this->bufsize = bufsize;
                WSAStartup(MAKEWORD(2, 0), &this->wsaData);   //MAKEWORD(2, 0) : winsock ver. 2.0
                this->sock = socket(AF_INET, SOCK_DGRAM, 0);  //AF_INET : IPv4、SOCK_DGRAM : UDP SOCK_STREAM : TCP
                if (this->sock < 0) { 
                    perror("socket() failed");
                    this->~UDP();
                }
            }
            ~UDP(){
                closesocket(this->sock); 
                WSACleanup();
            }
            int get_sock(){
                return this->sock;
            }
            void set_sock(int sock){
                this->sock = sock;
            }
            int port_send(struct sockaddr_in *addr, char *msg){ /* 送信 */
                int len = strlen(msg);
                int addrSize = sizeof(*addr);
                if (sendto(this->sock, msg, len, 0, (struct sockaddr *)addr, addrSize) != len){
                    perror("sendto() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_bind(struct sockaddr_in *addr){ /* ポートに結びつける */
                int addrSize = sizeof(*addr);
                if (bind(this->sock, (struct sockaddr *)addr, addrSize) < 0) { 
                    perror("bind() failed");
                    return 1;
                }
                return 0;
            }
            
            int port_recv(struct sockaddr_in *caddr, char* buff){ /* 受信する */
                int bytes;
                int csize = sizeof(*caddr);
            
                bytes = recvfrom (this->sock, buff, this->bufsize - 1, 0, (struct sockaddr *)caddr, &csize);
                if ((bytes) < 0) { // 空文字をエラーにしない
                    perror("recvfrom() failed");
                    return 1;
                }
                buff[bytes] = '\0'; /* 文字列として扱うため最後を \0 で終端して表示する */ 
                return 0;
            }

    };

    #define TRAY_H
    #define WM_TRAY_CALLBACK_MESSAGE (WM_USER + 1)
    #define WC_TRAY_CLASS_NAME "TRAY"
    #define ID_TRAY_FIRST 1000
    HMENU   trayMenuItem;
    struct tray_menu;

    struct tray {
        char *icon;        
        struct tray_menu *menu;
    };

    struct tray_menu {
        char *text;
        int disabled;
        int checked;

        void (*cb)(struct tray_menu *);
        void *context;

        struct tray_menu *submenu;
    };

    class TaskTray{ //タスクトレイ
        protected:
            WNDCLASSEX      wc;
            NOTIFYICONDATA  nid;
            HWND            hwnd;
            UINT            id;

        public:
            HMENU _tray_menu(struct tray_menu *m) {
                HMENU hMenu = CreatePopupMenu();
                for (; m != NULL && m->text != NULL; m++, (this->id)++) {
                    if (strcmp(m->text, "-") == 0) {
                        InsertMenu(hMenu, this->id, MF_SEPARATOR, TRUE, "");
                    } 
                    else {
                        MENUITEMINFO item;
                        memset(&item, 0, sizeof(item));
                        item.cbSize = sizeof(MENUITEMINFO);
                        item.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_DATA;
                        item.fType = 0;
                        item.fState = 0;
                        if (m->submenu != NULL) {
                            item.fMask = item.fMask | MIIM_SUBMENU;
                            item.hSubMenu = this->_tray_menu(m->submenu);
                        }
                        if (m->disabled) {
                            item.fState |= MFS_DISABLED;
                        }
                        if (m->checked) {
                            item.fState |= MFS_CHECKED;
                        }
                        item.wID = this->id;
                        item.dwTypeData = m->text;
                        item.dwItemData = (ULONG_PTR)m;

                        InsertMenuItem(hMenu, this->id, TRUE, &item);
                    }
                }
                return hMenu;
            }

            int tray_loop(int blocking) {
                MSG msg;
                if (blocking) {
                    GetMessage(&msg, NULL, 0, 0);
                } 
                else {
                    PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
                }
                if (msg.message == WM_QUIT) {
                    return -1;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                return 0;
            }

            void tray_update(struct tray *taskTray) {
                HMENU prevmenu = trayMenuItem;
                trayMenuItem = this->_tray_menu(taskTray->menu);
                SendMessage(this->hwnd, WM_INITMENUPOPUP, (WPARAM)trayMenuItem, 0);
                HICON icon;
                ExtractIconEx(taskTray->icon, 0, NULL, &icon, 1);
                if (this->nid.hIcon) {
                    DestroyIcon(this->nid.hIcon);
                }
                this->nid.hIcon = icon;
                Shell_NotifyIcon(NIM_MODIFY, &nid);

                if (prevmenu != NULL) {
                    DestroyMenu(prevmenu);
                }
            }

            TaskTray(std::string menuName) {
                this->id = ID_TRAY_FIRST;
                memset(&this->wc, 0, sizeof(this->wc));
                this->wc.cbSize = sizeof(WNDCLASSEX);
                this->wc.lpfnWndProc = (WNDPROC)this->_tray_wnd_proc;
                this->wc.hInstance = GetModuleHandle(NULL);
                this->wc.lpszClassName = WC_TRAY_CLASS_NAME;
                this->wc.lpszMenuName = menuName.c_str();
                if (!RegisterClassEx(&this->wc)) {
                    return;
                }

                this->hwnd = CreateWindowEx(0, WC_TRAY_CLASS_NAME, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                if (this->hwnd == NULL) {
                    return;
                }
                UpdateWindow(this->hwnd);

                memset(&this->nid, 0, sizeof(this->nid));
                this->nid.cbSize = sizeof(NOTIFYICONDATA);
                this->nid.hWnd = this->hwnd;
                this->nid.uID = 0;
                this->nid.uFlags = NIF_ICON | NIF_MESSAGE;
                this->nid.uCallbackMessage = WM_TRAY_CALLBACK_MESSAGE;
                lstrcpy( this->nid.szTip, TEXT(menuName.c_str())); 
                Shell_NotifyIcon(NIM_ADD, &this->nid);
                return;
            }
            void tray_exit() {
                Shell_NotifyIcon(NIM_DELETE, &this->nid);
                if (this->nid.hIcon != 0) {
                    DestroyIcon(this->nid.hIcon);
                }
                if (trayMenuItem != 0) {
                    DestroyMenu(trayMenuItem);
                }
                PostQuitMessage(0);
                UnregisterClass(WC_TRAY_CLASS_NAME, GetModuleHandle(NULL));
            }

            static LRESULT CALLBACK _tray_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
                switch (msg) {
                    case WM_CLOSE:
                        DestroyWindow(hwnd);
                        return 0;
                    case WM_DESTROY:
                        PostQuitMessage(0);
                        return 0;
                    case WM_TRAY_CALLBACK_MESSAGE:
                        switch (lparam){
                            case WM_LBUTTONUP:
                            case WM_RBUTTONUP:
                                POINT p;
                                GetCursorPos(&p);
                                SetForegroundWindow(hwnd);
                                WORD cmd = TrackPopupMenu(
                                    trayMenuItem, TPM_LEFTALIGN | 
                                    TPM_RIGHTBUTTON | 
                                    TPM_RETURNCMD | 
                                    TPM_NONOTIFY,
                                    p.x, 
                                    p.y, 
                                    0, 
                                    hwnd, 
                                    NULL
                                );
                                SendMessage(hwnd, WM_COMMAND, cmd, 0);
                                return 0;
                        }
                        break;
                    case WM_COMMAND:
                        if (wparam >= ID_TRAY_FIRST) {
                            MENUITEMINFO item = {
                                .cbSize = sizeof(MENUITEMINFO), .fMask = MIIM_ID | MIIM_DATA,
                            };
                            if (GetMenuItemInfo(trayMenuItem, wparam, FALSE, &item)) {
                                struct tray_menu *menu = (struct tray_menu *)item.dwItemData;
                                if (menu != NULL && menu->cb != NULL) {
                                    menu->cb(menu);
                                }
                            }
                            return 0;
                        }
                        break;
                }
                return DefWindowProc(hwnd, msg, wparam, lparam);
            }
    };

    /** 
     * @param text タイトル
     */
    class IOSet {
        protected:
            std::string appTitle; //コマンドプロンプトのタイトル
            std::string pwdPath; //カレントディレクトリ
            std::string appPath; //ファイルパス
            std::string appPathNoEX; //ファイルパス(拡張子無し)
        
        public:
            IOSet(std::string text = "タイトル") {
                std::string cmdLn;
                char path[256];
                this->appTitle = text;
                if (this->appTitle != ""){
                    this->title(this->appTitle);
                }
                GetCurrentDirectory(sizeof(path), path);
                this->pwdPath = path;
                GetModuleFileName(NULL, path, sizeof(path));
                this->appPath = path;
                str pathData(path);
                this->appPathNoEX = pathData.replace_all(".exe", "");
            }
        
            std::string title(std::string stringText = ""){
                if (stringText != ""){
                    this->appTitle = stringText;
                    cmd("title " + this->appTitle);
                }
                return this->appTitle;
            }
            
            std::string print(std::string stringText, std::string stringEnd = "\n") {
                std::cout << stringText << stringEnd << std::flush;
                return stringText;
            }
            std::string input(std::string stringPrompt = "") {
                std::string inputText;
                if (stringPrompt != ""){
                    std::cout << stringPrompt << std::endl; // 「std::endl」 \n とバッファをフラッシュ
                }
                std::getline(std::cin, inputText);
                return inputText;
            }
            std::string cmd(std::string stringCmd) {
                system(stringCmd.c_str());
                return stringCmd;
            }
            int create_process_cmd(std::string stringCmd){
                std::string cmdLog = "";
                cmdLog = stringCmd;
                STARTUPINFO si;
                PROCESS_INFORMATION pi;
                ZeroMemory( &si, sizeof(si) );
                si.cb = sizeof(si);
                ZeroMemory( &pi, sizeof(pi) );
                // Start the child process. 
                CreateProcess( 
                    NULL,   // No module name (use command line)
                    TEXT((char*)cmdLog.c_str()),        // Command line
                    NULL,           // Process handle not inheritable
                    NULL,           // Thread handle not inheritable
                    FALSE,          // Set handle inheritance to FALSE
                    0,              // No creation flags
                    NULL,           // Use parent's environment block
                    NULL,           // Use parent's starting directory 
                    &si,            // Pointer to STARTUPINFO structure
                    &pi            // Pointer to PROCESS_INFORMATION structure
                );
            
                Sleep(100); //起動出来るまで待つ
            
                // Close process and thread handles. 
                CloseHandle( pi.hProcess );
                CloseHandle( pi.hThread );
            
                return 0;
            }
        
            // プロセスハンドルから特権名を有効/無効
            BOOL ProcessPrivilegeName(HANDLE hProcess, LPCTSTR lpPrivilegeName, BOOL bEnable) {
                HANDLE              hToken; // アクセストークンのハンドル
                LUID                luid;   // LUID(ローカル・ユニークID)
                TOKEN_PRIVILEGES    tp;     // 特権トークン情報
            
                if (!OpenProcessToken(hProcess, OPEN_PROCESS_TOKEN, &hToken)) {
                    return FALSE;
                }
            
                if (!LookupPrivilegeValue(NULL, lpPrivilegeName, &luid)) { // 特権名のLUIDを取得
                    CloseHandle(hToken);
                    return FALSE;
                }
            
                tp.PrivilegeCount = 1; // 特権数
                tp.Privileges[0].Luid = luid; // 識別子
                tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

                // 特権トークン状態の有効/無効
                BOOL result = AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL) && GetLastError() == ERROR_SUCCESS;
            
                CloseHandle(hToken);
                return result;
            }
            int shutdown(std::string op,int second){
                int uFlag;
                if (op == "logoff"){
                    uFlag = EWX_LOGOFF;
                }
                else if(op == "shutdown"){
                    uFlag = EWX_SHUTDOWN;
                }
                else if(op == "reboot"){
                    uFlag = EWX_REBOOT;
                }
                else{
                    return -1;
                }
                Sleep(second * 1000);
            
                // ログオフ/シャットダウン/再起動を実行する
                if(this->ProcessPrivilegeName( GetCurrentProcess(), SE_SHUTDOWN_NAME, TRUE )){
                    ExitWindowsEx( uFlag, 0 );
                }
                return 0;
            }
        
            std::string path(int mode) {
                switch(mode){
                    case 1:
                        return this->appPathNoEX;
                    default:
                        return this->appPath;
                }
            }
            std::string pwd() {
                return this->pwdPath;
            }

            /**
             * @brief
             * メッセージボックスを作成
             * @param tit タイトル
             * @param tex テキスト
             * @param button 0.[OK] 1.[OK][キャンセル] 2.[中止][再試行][無視] 3.[はい][いいえ][キャンセル] 4.[はい][いいえ] 5.[再試行][キャンセル]
             * @param icon 0.なし 1.注意 2.情報 3.質問 4.警告
             * @param help 0.なし 1.あり
             * @return int
             */
            int MsgBox(
                std::string msgBoxTitle = "タイトル",
                std::string msgBoxText = "テキスト",
                int button = 0,
                int icon = 0,
                int help = 0
            ){
                int ans;
                int forms = 0;
                switch(button){
                    case 1:
                        forms = MB_OKCANCEL;
                        break;
                    case 2:
                        forms = MB_ABORTRETRYIGNORE;
                        break;
                    case 3:
                        forms = MB_YESNOCANCEL;
                        break;
                    case 4:
                        forms = MB_YESNO;        
                        break;
                    case 5:
                        forms = MB_RETRYCANCEL;
                        break;
                    default:
                        forms = MB_OK;
                        break;
                }
                switch(icon){
                    case 1:
                    case MB_ICONWARNING:
                        forms |= MB_ICONWARNING;
                        break;
                    case 2:
                    case MB_ICONINFORMATION:
                        forms |= MB_ICONINFORMATION;
                        break;
                    case 3:
                    case MB_ICONQUESTION:
                        forms |= MB_ICONQUESTION;
                        break;
                    case 4:
                    case MB_ICONERROR:
                        forms |= MB_ICONERROR;
                        break;
                    default:
                        break;
                }
                switch(help){
                    case 1:
                    case MB_HELP:
                        forms |= MB_HELP;
                        break;
                    default:
                        break;
                }
                ans = MessageBox(NULL , msgBoxText.c_str(), msgBoxTitle.c_str(), forms );
                return ans;
            }
            std::string read_file(std::string filePath){
                std::ifstream ifs(filePath);
                std::string fileData = "";
                std::string str;
                if (ifs.fail()) {
                    return "FALSE";
                }
                while (std::getline(ifs, str)) {
                    fileData = fileData + str + "\n";
                }
                return fileData;
            }
            
            int write_file(std::string filePath, std::string data, std::string mode = "a"){
                if (mode == "a"){
                    if (filePath == this->appPathNoEX + ".cpp" || filePath == this->appPath){
                        int ans;
                        ans = this->MsgBox("警告", "このプログラムの重要ファイルです。\n書き換えますか？", 4, 1, 0);
                        if (ans == IDNO){
                            this->print("アクセス拒否されました。");
                            return 2;
                        }
                    }
                    std::string sdata = read_file(filePath); //データ読み込み
                    std::ofstream ofs(filePath); //空ファイルにする
                    if (ofs.fail()){
                        this->print("FALSE");
                        return -1;
                    }
                    ofs << sdata << data << std::endl;
                    this->print(filePath + "に追加書き込み完了しました。");
                    return 0;
                }
                else if (mode == "w"){
                    if (filePath == this->appPathNoEX + ".cpp" || filePath == this->appPath){
                        int ans;
                        ans = this->MsgBox("警告", "このプログラムの重要ファイルです。\nエディタで書き換えてください！！", 0, 4, 0);
                        this->print("アクセス拒否されました。");
                        return -1;
                    }
                    std::ofstream ofs(filePath); //空ファイルにする
                    if (ofs.fail()){
                        this->print("FALSE");
                        this->print("書き込み失敗");
                        return -1;
                    }
                    ofs << data << std::endl;
                    this->print(filePath + "に書き込み完了しました。");
                    return 0;
                }
                else{
                    this->print("モードが違います。");
                    return -1;
                }
            }
            std::vector<int> get_now_time() {
                time_t t = time(nullptr);
                struct tm* nowTime = localtime(&t);
                std::vector<int> value = {
                    nowTime->tm_year + 1900,
                    nowTime->tm_mon + 1,
                    nowTime->tm_mday,
                    nowTime->tm_hour,
                    nowTime->tm_min,
                    nowTime->tm_sec
                };
                return value;
            }
            int random_num() {
                std::random_device rnd;
                return rnd();
            }
    };

#else

#endif



//TaskTray taskTray("ABC");
//void finish(tray_menu *){
//    taskTray.tray_exit();
//}
//void func1(tray_menu *){
//    IOSet io("");
//    io.create_process_cmd("winver");
//}
//
//tray tray_form ={               // タスクトレイの設定
//    (char*)"icon.ico", // タスクトレイのアイコン画像。別途用意しておく。
//    (tray_menu[]){
//        {(char*)"Settings",0,0,func1},
//        {(char*)"-"},                 // セパレータ
//        {(char*)"Quit",0,0,finish},   //終了
//        {nullptr}                     //最後の要素。必須。
//    }
//};
//int main(int argc, char *argv[]) {
//    taskTray.tray_update(&tray_form);
//    while(taskTray.tray_loop(1) == 0){} //タスクトレイが表示されている間ループ
//    return 0;
//}

//int main(int argc, char *argv[]){
//    IOSet io("APP");
//    io.cmd("notepad");
//    return 0;
//}