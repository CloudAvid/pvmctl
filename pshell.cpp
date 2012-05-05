#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
#include <vector>
using std::vector;

string version = "1.0.0";

/**
 * \class pshell
 * pvm shell
 */
class PShell
{
private:
	/**
	 * user command.
	 */
	string cmd;
	/**
	 * pipe character.
	 */
	char pchar;
	/**
	 * sub commands of the original command base on positions of 
	 * pipe character
	 */
	vector<string> subCmds;
	/**
	 * Piped command prefix.
	 * by this we can destinguished between first and piped 
	 * command in pshell.sh 
	 */
	string pcp;
public:
	PShell() {}
	void set_cmd(string _cmd) 
	{ 
		cmd = _cmd; 
		subCmds.clear();
	}
	void set_pchar(char pc) { pchar = pc; }
	void set_pcp(string _pcp) { pcp = _pcp; }
	void exec();
};

void PShell::exec()
{
	/* start of command and position of pipe.
	 */
	int cmd_start = 0, ps = -1;
	// define piped commands
	while ((ps = cmd.find(pchar, ps + 1)) != string::npos) {
		if (cmd[ps + 1] == '|') {
			++ ps;
			continue;
		}
		subCmds.push_back(cmd.substr(cmd_start, ps - cmd_start));
		cmd_start = ps + 1;
	}
	subCmds.push_back(cmd.substr(cmd_start));

	int numChilds = subCmds.size();
	int runChilds = 0;

	int fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	int fds[2] = {STDIN_FILENO, STDOUT_FILENO};
	for (int i = 0; i < numChilds; ++i) {
		/* store write side of previos created pipe,
		 * it would be closed in next adjacent child.
		 */
		int old_fd_out = fd_out;
		/* if we are not on last child ...
		 */
		if ((i + 1) != numChilds) {
			/* we create a pipe: communicate way this child 
			 * and the next (adjacent) child.
			 */
			if (pipe(fds) < 0) {
				perror("pshell-pipe");
				cout << "can't create pipe .." << std::endl;
				goto waiting;
			}
			/* store write side for child.
			 */
			fd_out = fds[1];
		} else 
			/* we are on last child and should out on STDOUT_FILENO
			 */
			fd_out = STDOUT_FILENO;

		int ret = fork();
		if (ret == 0) {
			/* close write side of previos created pipe ..
			 * we use only read side of him.
			 */
			if (old_fd_out != STDOUT_FILENO) close(old_fd_out);
			if (dup2(fd_out, STDOUT_FILENO) < 0) {
				perror("pshell");
				cout << "can't duplicate output stream ...";
				exit(EXIT_FAILURE);
			}
			if (dup2(fd_in, STDIN_FILENO) < 0) {
				perror("pshell");
				cout << "can't duplicate input stream ...";
				exit(EXIT_FAILURE);
			}
			/* add prefix for piped commands
			 */
			if (i != 0) subCmds[i] = pcp + subCmds[i];
			execlp("/bin/bash", "pshell", "/bin/pshell.sh", subCmds[i].c_str(), (char *) NULL);
			perror("pshell");
			exit(EXIT_FAILURE);
		} else if (ret > 0) {
			++ runChilds;
			/* store read side for next child 
			 */
			fd_in = fds[0];
			/* close writnig side of open pipes in parent
			 */
			if (fds[1] != STDOUT_FILENO) close(fds[1]);
		} else {
			cout << "can't run command .." << std::endl;
			goto waiting;
		}
	}
waiting:
	for (int i = 0; i < runChilds; ++i) {
		int status;
		if (wait(&status) == -1)
			perror("wait error");
	}
}

// test accurance of special characters in the command
bool is_injection_possible(string cmd)
{
	if (cmd.find('`') != string::npos &&
			cmd.find("$(") != string::npos)
		return true;
	return false;
}

int main(int argc, char *argv[])
{
	string cmd;
	PShell pshell;
	pshell.set_pchar('|');
	pshell.set_pcp("PIPED ");

	if ((argc > 1) && (! strncmp(argv[1], "-c", 2)) && 
					(argv[2] != (char *) NULL)) {
		/* called with command throw ssh or su or ...
		 */
		pshell.set_cmd(string(argv[2]));
		pshell.exec();
		exit(EXIT_SUCCESS);
	}

	while (1) {
	try {
		cout <<  "pvm > ";
		std::getline(cin, cmd);

		if (cmd.empty()) continue;
		else if (cmd == "version") {
			cout << version << std::endl;
			continue;
		}
		else if (cmd == "exit") exit(EXIT_SUCCESS);

		pshell.set_cmd(cmd);
		pshell.exec();
	} catch (std::exception e) {
		cout << e.what() << std::endl;
	}
	} //while
}
