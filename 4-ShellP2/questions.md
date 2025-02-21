1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  fork() is used to create a new child process so  "execvp()" doesn't replace the shell itself. "fork()" allows us to create a separate child process to run the command while keeping the shell running in the parent process.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If fork() fails, it means the system reached its process limit or is out of resources. when this happens, fork() returns -1, and my implementation should check for this failure and print an error message before continuing. If fork() fails, the shell should not proceed with execvp() since there is no child process to run it.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  execvp() find the command to execute by searching for the  command in the directories listed in the PATH environment variable. The PATH variable will contains directories where executable files are stored and if the command is not found in these directories, execvp() will fail and return an error.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  The purpose is to prevent processes that have completed execution to remain in the process table and the function makes the parent process wait for the child process to complete. If we didn't call it, it would lead to resource leaks over time.  

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**: WEXITSTATUS(status) will get the exit code of the child process from the status returned by wait() and this is important because it helps the shell know if the command ran successfully with an exit status 0 or it ran into errors which is when an exit status of nonzero is returned. 
    
6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**: build_cmd_buff() handles quoted arguments by checking for double quotes (" ") and when its found, everything inside the quotes is treated as a single argument rather than splitting it at spaces. This is necessary because users need to pass arguments with spaces like filenames or phrases. 

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  The main changes included correctly processing quoted arguments and incorporating logic to handle external commands separately. There were no unexpected challenges in refactoring your old code. 

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  Purpose of signals in a Linux system is allows the kernel or processes to send asynchronous notifications to other processes and they differ from other forms of (IPC) because signals are simple notifications that inform a process of an event, such as termination, suspension, or user-defined actions and IPC allows structured data exchange between processes

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGKILL(9) forcefully stops a process immediately without cleanup. It can’t be ignored or handled. This is typically used when a process is completely unresponsive. SIGTERM (15) ask a process to shut down and gives it time to clean up. This is the preferred way to stop a process. SIGINT (2) is sent when you press Ctrl + C. It will interrupt a process and let it handle cleanup before exiting.
     
- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**: when a process receives SIGSTOP then it pauses immediately. It cannot be ignored or caught like SIGINT by the process because it is directly enforced by the kernel.
