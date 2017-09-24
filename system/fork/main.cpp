#include <iostream>
#include <string>
#include <cmath>

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

const Family myFamily = Family::Mess;
const size_t depth = 4;
size_t currentDepth = 0;

std::string history;

void doFork();

void parent(const pid_t childPid) {
	SUPER_GLOBAL_NAME += "parent ";
	history += "P";

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
	history += "C";

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

size_t getNbTotalProc() {
	switch (myFamily) {
		case Family::OnlyChildren:
		case Family::GrandChildren:
			return depth + 1;
			break;
		case Family::Mess:
			return std::pow(2, depth);
			break;
	}
}

size_t getId() {
	size_t id = 0;
	switch (myFamily) {
		case Family::OnlyChildren: {
			id = std::max(0, static_cast<int>(history.find('C') + 1));
		} break;
		case Family::GrandChildren: {
			while (history[id] != 'P' && id < history.size())
				++id;
		} break;
		case Family::Mess: {
			for (size_t i = 0; i < history.size(); ++i) {
				id = id << 1;
				if (history[i] == 'C')
					id |= 0x1;
			}
		} break;
	}
	return id;
}

int main()
{
	if (depth > 0)
		doFork();

	cout << "id: " << getId() << "\tpid: " << getpid() << "\tparent: " << getppid() << "\thistory: " << history << endl;

	size_t dep = listSize/getNbTotalProc()*getId(), step = listSize/getNbTotalProc();
	cout << "[" << dep << ", " << dep + step << "[" << endl;
	for (size_t i = 0; i < step; ++i)
		cout << dep + i << ", ";
	cout << endl;

	return 0;
}
