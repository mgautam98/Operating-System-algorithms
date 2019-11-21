#include<stdio.h>
#include<sys/types.h>

void printDetails(){
        printf("%d : process id is : %d\n",getpid(),getpid());
        printf("%d : parent id is : %d\n",getpid(),getppid());
        printf("%d : real user id is : %d\n",getpid(),getuid());
        printf("%d : effective user id is : %d\n",getpid(),geteuid());
        printf("%d : group id is : %d\n",getpid(),getgid());
        printf("%d : effective group id is : %d\n",getpid(),getegid());
}

int main(){
        pid_t pid = fork();
        if(pid>0){
                printDetails();
                printf("%d : child id is %d\n",getpid(),pid);
        }else{
                printDetails();
                printf("%d : i am child of %d\n",getpid(),getppid());
        }
        return 0;
}