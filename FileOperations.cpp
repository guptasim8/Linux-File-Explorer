#include "header"
extern char **environ;
void openFile(string filename){
    pid_t newProcess;
    char* argv[]={"nano",new char[filename.size()+1],NULL};
    strcpy(argv[1],filename.c_str());
    int status=posix_spawn(&newProcess,"/bin/nano",NULL,NULL,argv,environ);
    if(status==0){
        //newProcess created
        //hold existing process
        waitpid(newProcess,&status,0);//child exit
    }else{
        cout<<"Unable to open file"<<strerror(status)<<"\n";
    }
}
