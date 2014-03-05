#include <iostream>
#include <fstream>

#include <Windows.h>
#include <tchar.h>

#include "Scanner.h"
#include "Parser.h"

#include "Node.h"
#include "Tokens.h"

#include "VM.h"

using namespace std;

int main(int argc, char *argv[])
{
	SetConsoleTitle(L"Ostkaka's Compiler");
	for (int i = 0; i < argc; i++)
	{
		//cout << i << ": " << argv[i] << std::endl;
	}

	cout << std::endl << "Compiling..." << endl << endl;

	if (argc >= 2)
	{
		ifstream stream;
		Scanner scanner;
		Parser parser;
		vector<Token*> tokens;
		vector<Statement*> code;

		stream.open(argv[1]);

		stream.unsetf(ios_base::skipws);

		tokens = scanner.Scan(stream);

		stream.close();

		code = parser.ParseStmt(tokens, true);

		for (auto stmt : code)
			cout << endl << stmt->toString() << endl << endl;

		cout << "Compilation done!" << endl;

		cout << endl << "output:" << endl;

		VM vm;

		for (auto stmt : code)
			vm.Execute(stmt);
	}
	else
	{
		cout << "Could not find file!" << endl;
	}

	cin.get();

	return 0;
}