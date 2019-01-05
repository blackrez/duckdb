//===----------------------------------------------------------------------===//
//                         DuckDB
//
// execution/operator/scan/physical_table_function.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "execution/physical_operator.hpp"
#include "storage/data_table.hpp"

namespace duckdb {

//! Represents a scan of a base table
class PhysicalTableFunction : public PhysicalOperator {
public:
	PhysicalTableFunction(LogicalOperator &op, TableFunctionCatalogEntry *function,
	                      unique_ptr<Expression> function_call)
	    : PhysicalOperator(PhysicalOperatorType::TABLE_FUNCTION, op.types), function(function),
	      function_call(move(function_call)) {
	}

	//! Function to call
	TableFunctionCatalogEntry *function;
	//! Expressions
	unique_ptr<Expression> function_call;

	void _GetChunk(ClientContext &context, DataChunk &chunk, PhysicalOperatorState *state) override;

	unique_ptr<PhysicalOperatorState> GetOperatorState(ExpressionExecutor *parent_executor) override;
};

class PhysicalTableFunctionOperatorState : public PhysicalOperatorState {
public:
	PhysicalTableFunctionOperatorState(ExpressionExecutor *parent_executor)
	    : PhysicalOperatorState(nullptr, parent_executor), initialized(false) {
	}

	unique_ptr<TableFunctionData> function_data;
	bool initialized;
};

} // namespace duckdb