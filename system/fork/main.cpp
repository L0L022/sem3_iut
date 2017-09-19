#include <iostream>
#include <string>

#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

string SUPER_GLOBAL_NAME;
const size_t listSize = 100;

enum class Family {
	OnlyChildren,
	GrandChildren,
	Mess
};

const Family myFamily = Family::GrandChildren;
const size_t depth = 20;
size_t currentDepth = 0;

void doFork();

void parent(const pid_t childPid) {
	SUPER_GLOBAL_NAME += "parent ";

	// int status;
	// waitpid(childPid, &status, 0);
	//
	// for (size_t i = 1; i <= listSize/2; i++)
	// 	cout << i << endl;
	switch (myFamily) {
		case Family::OnlyChildren:
			if (currentDepth < depth)
				doFork();
			break;
		case Family::GrandChildren:
			break;
		case Family::Mess:
			if (currentDepth < depth)
				doFork();
			break;
	}

	int status;
	waitpid(childPid, &status, 0);
}

void child() {
	SUPER_GLOBAL_NAME += "child ";

	// for (size_t i = listSize/2; i <= listSize; i++)
	// 	cout << i << endl;

	switch (myFamily) {
		case Family::OnlyChildren:
			break;
		case Family::GrandChildren:
			if (currentDepth < depth)
				doFork();
			break;
		case Family::Mess:
			if (currentDepth < depth)
				doFork();
			break;
	}
}

void doFork() {
	++currentDepth;
	pid_t pidFork = fork();

	if (pidFork > 0)
		parent(pidFork);
	else
		child();
}

int main()
{
	if (depth > 0)
		doFork();

	cout << SUPER_GLOBAL_NAME << " pid: " << getpid() << " parent: " << getppid() << endl;

	return 0;
}
