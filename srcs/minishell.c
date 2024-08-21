#include "../includes/minishell.h"

void    run_minishell(char *input_str, t_env *env,
            t_node  *tokens, t_command_node *cmds)
{
    input_str = readline("Minishell > ");
    if (!input_str)
        
}

 int main(int ac, char **av, char **env)
{
    /*
    char    *str;
    t_node  tokens;
    */
    (void)ac;
    (void)av;
   /*char *env[] = {
        "PATH=/home/taha/.vscode-server/bin/fee1edb8d6d72a0ddff41e5f71a671c23ed924b9/bin/remote-cli:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/Common Files/Oracle/Java/javapath:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/dotnet/:/mnt/c/Program Files/Java/jdk-18.0.1.1/bin:/mnt/c/Program Files/Microsoft SQL Server/150/Tools/Binn/:/mnt/c/Program Files/Git/cmd:/mnt/c/Program Files/Microsoft SQL Server/Client SDK/ODBC/170/Tools/Binn/:/mnt/c/Users/taha ALbayda/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/taha ALbayda/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/taha ALbayda/.dotnet/tools:/snap/bin",
        "HOME=/home/user",
        "USER=myuser",
        "A=",
        "Z=teq:=",
        NULL
    };*/
   t_env *env_list = environment(env);
    // Print the environment variables
    
    t_env *current = env_list;
    while (current) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
     //Clean up: Free the environment list
    free_envlist(env_list);

    return 0;
}