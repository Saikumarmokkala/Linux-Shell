
/*

Name : SAI KUMAR REDDY MOKKALA
ID   : 1001728207

*/


#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"
#define MAX_COMMAND_SIZE 100

#define MAX_NUM_ARGUMENTS 12
#define MAX_HISTORY_COMMAND 15
#define SEMICOLON " ; "

// This function is for handling the signals
static void handle_signal(int signal)
{

}

// This function is for printing the last history 15 commands
void printhistory(int c, char  *history[])

{

        int i;
        int hist_count = c;  // Count variable for history where it will keep
                             //track of number of history commands
        /*
         Printing the history array for latest 15 commands
        */
        for (i=0; i< hist_count; i++)
        {

            printf("%d %s\n",i,history[i]);
        }

}

// Function for printing the listpids
void printlistpids(int c, int  pids[])
{

        int i;
        int pid_count = c; // Count variable to keeep track of number of listpids

         /*
         Printing the listpids array for last 15 commands
        */
        for (i=0; i< pid_count; i++){

            printf("%d %d\n",i,pids[i]);
        }

}






int main()
{



       // Sigaction struct handler for installing the ctrl-z and ctrl-c signals

       struct sigaction act;

       // Firstly structure is zeroed out so that we can add the signals whichever as per requirement

       memset (&act, '\0', sizeof(act));

       // sa_handler is a pointer to function and it is set to our desired function as per requirement

       act.sa_handler = &handle_signal;

       // Installing the handler for handling the signal
       // which is SIGTSTP in this case, so that it blocks ctrl-z signal.

       if (sigaction(SIGTSTP, &act, NULL) < 0)
       {

       return 1;

       }

       // Installing the handler for handling the signal
       // which is SIGINT in this case, so that it blocks ctrl-c signal

       if (sigaction(SIGINT, &act, NULL) < 0) {
       //perror ("sigaction: ");
       return 1;

       }

       // It will allocate the memory address of command line array
       char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

       char * history [15]; // Array for storing the history last 15 commands

       int pid_count = 0; // Intialization of variable pid_count foe keeping track of number of listpids

       int pids[15]; // Intialization of pids array for storing the last 15 commands

       int history_count = 0; // Intialization of variable history_count for keeping track of number of history commands

       pid_t pid = 0;
/*
       char strtoken[15][100];
       for(i=0; i <= 15; i++)

       {


          strtoken[i] = strtok(cmd_str, ";");

       }


      int index =0;
      int i=0;
      char arr[10][255];
      if(i<10)
      {

           if(token[i]!=';')
           {
                strncpy(arr[index],token[i], strlen(token[i);

                i++;
           }

      break;
      fork();
      execvp(arr[0], arr);



       }
*/





      while( 1 )
     {


           // It will print out the msh prompt


           printf ("msh> ");
           /*
           It will read the command from the command line. The size of the maximum command is
           MAX_COMMAND_SIZE. The while command will wait until the user will type something
           and it will return NULL if the user does not tyoe anything.
           */

           while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

           // Index after converting the specific number of history command which is a string at first
           int index = atoi( &cmd_str[1] );

           if(cmd_str[0] == '!')      // it will only enter when the command line is not null

           {      /*

                   In this if the index found is less than the history count,
                   it will take the string of specific history and convert it into the index of history
                   and with the help of index it will be copied to the command line array,
                   otherwise it will display command not in history.

                  */
                  int index = atoi( &cmd_str[1] );   // Index after converting the specific number of history command which is a string at first


                  memset( cmd_str,0, 100 );          // zeroed the cmd_str so that we can copy the history commands




                  if(index < history_count)
                  {
                     strncpy( cmd_str, history[index], strlen(history[index]));

                  }



                  else

                  printf("Command not in history.\n");

           }



           char *token[MAX_NUM_ARGUMENTS];   // Parse input;

           int   token_count = 0;            // Variable for counting tokens

           // Pointer to point to the token parsed by strsep

           char *arg_ptr;

           char *working_str  = strdup( cmd_str );
           /*
             we are going to move the working_str pointer so that it
             keep tracks of its original value because of this we can deallocate
             the correct amount at end
           */

           char *working_root = working_str;
           // We will be going to tokenize the input by whitespace as delimiter

           while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&(token_count<MAX_NUM_ARGUMENTS))

          {
                token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );

                if( strlen( token[token_count] ) == 0 )
                {
                    token[token_count] = NULL;
                }

                token_count++;
          }


          free(working_root);

          /*
          In this we are inserting pids in to the pids array so that the last 15 pids are stored
          and the latest commands are updated in the array for listing the process pids.
          */


          if(pid > 0)

          {

                if (pid_count <15)
                {

                    pids[pid_count] = pid;

                    pid_count++;

                    fflush(NULL);

                 }

                 else
                {
                    int i;

                    for(i=1; i< 15;i++)
                    {
                        pids[i-1]= pids[i];

                    }

                    pids [14]= pid;

                    pid_count = 15;


                }

           }

           /*

           In this, the history commands are inserted into the history array
           and the latest 15 history commands are updated continuosly

           */


          if(strlen(cmd_str)!=0)

          {

                 if (history_count <15)
                 {
                      history[history_count++] = token[0];

                 }

                else
                {

                     free(history[0]);
                     int i;

                     for(i=1; i< 15;i++)
                     {
                          history[i-1]= history[i];

                     }

                     history [14]= token[0];
                     history_count = 15;

                }


         }





         /* In this case if we don not give any input
            it will prompt to print msh
         */


        if( token [0]== NULL)
        {
               continue;
        }

        // If the user enters quit or exit in the mav shell it will come out of the shell

        else if (strcmp(token[0],"quit")== 0 || strcmp(token[0],"exit")== 0)
        {
               exit(0);
        }

        // If the user enters cd, mavshell will give access to change directory

        else if(strcmp(token [0],"cd")==0)
       {
              chdir(token [1]);
              fflush(NULL);
       }

        /* In this case, when the user enters bg, it will normally check the
           last child process state which has been suspended and will make it
           run by sending SIGCONT signal

        */

       else if( strcmp(token [0],"bg")==0)
       {
             kill(pids[pid_count-1], SIGCONT);
       }

       /*
        If the user enters history, it will show last 15 history commands
        or commands entered till that point if they are less than 15
       */

       else if(strcmp(token [0],"history")==0)
       {
             printhistory(history_count,history);

       }

       /*
         If the user enters listpids, it will show them the
         last 15 process id's or the pid's till that point
         if they are less than 15

       */

       else if(strcmp(token [0],"listpids")==0)
       {
             printlistpids(pid_count,pids);

       }

       /* If the user enters more than the max number
          of the arguments then it will stop running,
          it is out of bound check.
       */

       else if (token_count > MAX_NUM_ARGUMENTS)
      {
            pid =0;
      }

      // If the user enters big directory, it will be helpful for changing directory



     else
    {

         int exec;     // return value of execvp
         int status;   // variable for knowing the status of process

/*
        int index =0;
        int z,k;

        char *arr[MAX_NUM_ARGUMENTS];



        for (k=0; k< MAX_NUM_ARGUMENTS;k++)

        {
                 arr[k]= (char*)malloc( sizeof(char));

        }

        for (z=0;z< MAX_NUM_ARGUMENTS; z++)

        {


              if(token[z] != ";")
              {
                   arr[z] =strncpy(arr[index],token[z], strlen(token[z]));

                   index++;

              }

             else if(token[z]==";")

             {
                 continue;
             }


*/

        pid = fork();   // Here the parent process is forked


        /*

        If the child pid value is equal to zero,
        it will execute the child process. Now in
        this we use the combination of execvp and
        fork for taking all the processes of shell.
        Here wait is given in the parent(Pid >0)
        because the child has to execute first as it
        should be unique process.

        */


        if(pid ==0)
        {

              exec= execvp(token[0], token);

              if (exec == -1)

              {
                      printf("%s: Command not found.\n",*token);
                      pid =0;
                      break;

              }

             fflush(NULL);

        }


          else
         {

              wait( &status);

              fflush(NULL);

         }




      }


   }




  return 0;
}
