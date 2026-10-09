#pragma once

struct sqlite3_stmt;

namespace Database
{
	class Results;
	class Connection;

	class Command
	{
	public:
		Command(const Connection* connection = 0, sqlite3_stmt* stmt = 0):
			connection(connection), stmt(stmt)
		{}

		const Connection* connection;
		sqlite3_stmt* stmt;
	};

	// Partial SDK declaration; native database implementations remain external.
	class Connection
	{
	public:
		bool Execute(Results& kResults, const char* szCommand, int lenCommand = -1) const;
		const char* ErrorMessage() const;
		// TODO: Connection (remaining SDK methods and members).
	};
}
