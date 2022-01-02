#include "header"
void print_header(path p){
        ostringstream out;
        string full_path=string(absolute(p));
		struct stat fileStat;
        stat(p.filename().c_str(), &fileStat);
        //Unsigned It type User ID to user name and Group ID to group name
        struct passwd *pw = getpwuid(fileStat.st_uid);
		//full_path="\033[0;32m"+pw->pw_name+"@"+full_path+
		out << "\033[0;32m"<<pw->pw_name << "@"<<full_path<<":"<<"\033[0m";
		//string entry=  +entry+ "\033[0m";
		cout << out.str();
}
void processCommand(path p,string command){
    vector <string> tokens;
    stringstream cstream(command);
    string word="";
    int breakSp=1;
    for(int i=0;i<command.size();i++){
        if(command[i]=='\'')breakSp++;
        else if((breakSp&1)&&command[i]==' '){
            if(!word.empty())tokens.push_back(word);
            word="";
        }else word+=command[i];
    }
    if(!word.empty())tokens.push_back(word);
    if(tokens[0]=="copy"){
        int last=tokens.size()-1;
        const auto copyOptions = copy_options::overwrite_existing|copy_options::recursive;
        string dest="";
        dest=(tokens[last][0]=='.'&&tokens[last][1]=='/')?string(current_path())+"/"+tokens[last].substr(2):tokens[last];
        if(dest.back()!='/')dest+='/';
        cout<<"Files moved to "<<dest<<" successfully\n";
        for(int i=1;i<last;i++){
            if(directory_entry(tokens[i]).is_directory())
                copy(path(string(current_path())+"/"+tokens[i]),path(dest+tokens[i]),copyOptions);
            else
            copy(path(string(current_path())+"/"+tokens[i]),path(dest),copyOptions);
        }
    }
    else if(tokens[0]=="move"){
        if(directory_entry(tokens[1]).is_regular_file())
            rename(path(string(current_path())+"/"+tokens[1]),path(string(tokens[2])+"/"+tokens[1]));
    }
    else if(tokens[0]=="rename"){
        if(directory_entry(tokens[1]).is_regular_file())
            rename(path(string(current_path())+"/"+tokens[1]),path(string(current_path())+"/"+tokens[2]));
    }
    //else if(tokens[0]=="create_file"){}
    else if(tokens[0]=="create_dir"){ create_directory(path(string(current_path())+"/"+tokens[1]);}
    else if(tokens[0]=="del_file"){remove(path(string(current_path())+"/"+tokens[1]);}
    else if(tokens[0]=="del_dir"){remove_all(path(string(current_path())+"/"+tokens[1]);}
        //case "goto": break;
        //case "search": break;
    //}

}

bool enterCommandMode(path p){
    cout << CLEAR;
    print_header(p);
    string command="";
    while(true){
        char c=cin.get();
        if(c==8||c==127){
            if(command.empty())continue;
            cout<<"\b \b";
            command.pop_back();
        }
        else if(c==27){
            //escape= go to normal mode
            return false;
        }
        else if(c==10){
            cout<<"\n";
            //enter
            if(command=="q"){
                    return true;
            }
            processCommand(p,command);
            p=current_path();
            command="";
            print_header(p);

        }
        else{
            command+=c;
            cout<<c;
        }
    }
    return false;
}
