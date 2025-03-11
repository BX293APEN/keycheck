#include "ioset.hpp"

class KeyCheck : public IOSet{
    protected:
        std::unordered_map <int, std::string> keyList{ //連想配列を使える
            {VK_LSHIFT,     "LSHIFT"},
            {VK_RSHIFT,     "RSHIFT"},
            {VK_LCONTROL,   "LCTRL"},
            {VK_RCONTROL,   "RCTRL"},
            {VK_LMENU,      "LALT"},
            {VK_RMENU,      "RALT"},
            {VK_SPACE,      "SPACE"},
            {VK_LWIN,       "LWIN"},
            {VK_RWIN,       "RWIN"},
            {VK_UP,         "UP"},
            {VK_DOWN,       "DOWN"},
            {VK_LEFT,       "LEFT"},
            {VK_RIGHT,      "RIGHT"},
            {VK_RETURN,     "ENTER"},
            {VK_ESCAPE,     "ESC"},
            {VK_LBUTTON,    "LCLICK"},
            {VK_RBUTTON,    "RCLICK"},
            {VK_HOME,       "HOME"},
            {VK_END,        "END"},
            {VK_SPACE,      "SPACE"},
            {VK_F1,         "F1"},
            {VK_F2,         "F2"},
            {VK_F3,         "F3"},
            {VK_F4,         "F4"},
            {VK_F5,         "F5"},
            {VK_F6,         "F6"},
            {VK_F7,         "F7"},
            {VK_F8,         "F8"},
            {VK_F9,         "F9"},
            {VK_F10,         "F10"},
            {VK_F11,         "F11"},
            {VK_F12,         "F12"},
            {VK_F13,         "F13"},
            {VK_F14,         "F14"},
            {VK_F15,         "F15"},
            {VK_F16,         "F16"},
            {VK_F17,         "F17"},
            {VK_F18,         "F18"},
            {VK_F19,         "F19"},
            {VK_F20,         "F20"},
            {VK_F21,         "F21"},
            {VK_F22,         "F22"},
            {VK_F23,         "F23"},
            {VK_F24,         "F24"},
            {'1',   "1"},
            {'2',   "2"},
            {'3',   "3"},
            {'4',   "4"},
            {'5',   "5"},
            {'6',   "6"},
            {'7',   "7"},
            {'8',   "8"},
            {'9',   "9"},
            {'0',   "0"},
            {'A',   "a"},
            {'B',   "b"},
            {'C',   "c"},
            {'D',   "d"},
            {'E',   "e"},
            {'F',   "f"},
            {'G',   "g"},
            {'H',   "h"},
            {'I',   "i"},
            {'J',   "j"},
            {'K',   "k"},
            {'L',   "l"},
            {'M',   "m"},
            {'N',   "n"},
            {'O',   "o"},
            {'P',   "p"},
            {'Q',   "q"},
            {'R',   "r"},
            {'S',   "s"},
            {'T',   "t"},
            {'U',   "u"},
            {'V',   "v"},
            {'W',   "w"},
            {'X',   "x"},
            {'Y',   "y"},
            {'Z',   "z"}
        };

        struct ShortcutConfig{
            std::vector<std::string> key;
            std::string func;
        };
        std::vector<ShortcutConfig> shortcutList;

        std::vector<std::string> keyPressed, keyFlag, newKey;
        std::string keyState, shortcutFileName;

    public:
        KeyCheck(std::string title, std::string fileName) : IOSet(title){
            this->shortcutFileName = fileName;
            this->shortcut_data_read();
        }
        
        int key_state_check(void){
            this->keyPressed.clear();
            for(auto& [key, value] : this->keyList){
                if (GetKeyState(key) & 0x8000) this->keyPressed.push_back(value);
            }
            return 0;
        }

        std::string get_key_event(void){
            this->key_state_check();
            
            if(this->keyPressed.empty()){ // キーが押されていない場合
                this->keyState = "RELEASE";
                this->keyFlag.clear();
                return this->keyState;
            }
            else{
                vec pressedKeys = this->keyPressed;
                //this->print(pressedKeys.to_str());
                if(pressedKeys.vec_compare(this->keyFlag)){  //状態変化なし
                    this->keyState = "EQ";
                    //this->print(this->keyState);
                    return this->keyState;
                }
                else{
                    this->newKey.clear();
                    std::set_difference( // 差集合
                        this->keyPressed.begin(), this->keyPressed.end(), 
                        this->keyFlag.begin(), this->keyFlag.end(), 
                        std::back_inserter(this->newKey)
                    );
                    
                    if(this->newKey.empty()){
                        this->keyState = "RELEASE";
                        this->keyFlag.clear();
                        return this->keyState;
                    }
                    else{
                        this->keyFlag.clear();
                        std::copy(this->keyPressed.begin(), this->keyPressed.end(), std::back_inserter(this->keyFlag));
                        this->keyState = "NEWKEY";
                        return this->keyState;
                    }
                }
            }
        }

        int shortcut_data_read(void){
            if(read_file(this->shortcutFileName) == "FALSE"){
                return false;
            }
            else{
                std::vector<std::string> fileDataLine;
                ShortcutConfig shortcutConfig;
                str shortcutFileData            = read_file(this->shortcutFileName);
                fileDataLine                    = shortcutFileData.split("\n");
                this->shortcutList.clear();
                
                for(std::string &l : fileDataLine){
                    if (std::count(l.begin(), l.end(), '=') > 0){
                        shortcutConfig.key.clear();
                        shortcutConfig.func = "";
                        str shortcutData                            = l;
                        std::vector<std::string> shortcutFileLine   = shortcutData.split("=");
                        str shortcutKeyData                         = shortcutFileLine[0];
                        //vec shortcutKey                           = shortcutKeyData.split(",");
                        //this->print(shortcutKey.to_str());
                        shortcutConfig.key                          = shortcutKeyData.split(",");
                        shortcutConfig.func                         = shortcutFileLine[1];
                        this->shortcutList.push_back(shortcutConfig);
                    }
                }
                return true;
            }
        }

        int key_func(void){
            if (this->keyState != "NEWKEY"){
                return 2;
            }
            for(ShortcutConfig &l : this->shortcutList){
                vec registKeyCombination    = l.key;
                //this->print(registKeyCombination.to_str());
                if (registKeyCombination.vec_compare(this->keyPressed)){
                    //this->print(l.func);
                    //std::async(std::launch::async, system, l.func.c_str());
                    this->create_process_cmd(l.func);
                    Sleep(100);
                    return 1;
                }
            }
            return 0;
        }

        int main(void){
            this->get_key_event();
            this->key_func();
            return 0;
        }
};

IOSet io("");
KeyCheck keycheck("Keyboard Shortcut", io.pwd() + "\\keysc.ini");

TaskTray taskTray("KeyCheck");
int process = true;
void finish(tray_menu *){
    process=false;
    taskTray.tray_exit();  // タスクトレイから削除
}
void shortcut_setting(tray_menu *){
    io.create_process_cmd("notepad " + io.pwd() +"\\keysc.ini");
}

void shortcut_update(tray_menu *){
    keycheck.shortcut_data_read();
}

void help(tray_menu *){
    io.create_process_cmd("explorer " + io.pwd()+"\\README.md");
}

tray tray_form ={               // タスクトレイの設定
    (char*)"icon/icon.ico", // タスクトレイのアイコン画像。別途用意しておく。
    (tray_menu[]){
        {(char*)"Settings",0,0,shortcut_setting},
        {(char*)"Update",0,0,shortcut_update},
        {(char*)"-"},                 // セパレータ
        {(char*)"Quit",0,0,finish},   //終了
        {(char*)"-"},
        {(char*)"Help",0,0,help},
        {nullptr}                     //最後の要素。必須。
    }
};

//キーの取得
void key_check(void){
    while(process){
        keycheck.main();
        Sleep(100);
    }
}

int main(int argc, char *argv[]) {
    std::thread keyboard(key_check);// 表示処理は別スレッド化
    taskTray.tray_update(&tray_form); //タスクトレイに登録
    while(taskTray.tray_loop(1) == 0){} //タスクトレイが表示されている間ループ
    keyboard.join();
    return 0;
}