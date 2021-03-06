#include "duckdb/parser/statement/explain_statement.hpp"
#include "duckdb/parser/transformer.hpp"

namespace duckdb {

using namespace duckdb_libpgquery;

unique_ptr<ExplainStatement> Transformer::TransformExplain(PGNode *node) {
	PGExplainStmt *stmt = reinterpret_cast<PGExplainStmt *>(node);
	D_ASSERT(stmt);
	return make_unique<ExplainStatement>(TransformStatement(stmt->query));
}

} // namespace duckdb
