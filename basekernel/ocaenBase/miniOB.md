creatTable:

- parse_stage_：`.y` `.i` -> set_sql_node
- resolve_stage_：`Stmt::create_stmt`  -> set_stmt
- optimize_stage_：无`logicalPlan` 无`physicalPlan`
- execute_stage_：
  - 无物理计划，走`command_executor` 
  - 否则，走`handle_request_with_physical_operator`



1. 有物理计划： `operator`
2. 无物理计划：`excutor`
3. 物理计划调用栈，插入为例

```cpp
table_->make_record && trx->insert_record

RC InsertPhysicalOperator::open(Trx *trx)

operator_->open(trx);
rc = sql_result->open(); 
RC PlainCommunicator::write_result_internal
```



基本io操作



头文件怎么导入，有哪些工具类

![image-20241021215537554](https://my-pic.miaops.sbs/2024/10/image-20241021215537554.png)



### 添加新类型

- 语法与词法： `.l` `.y` 
- 类型枚举类：`attr_type.h` `attr_type.cpp`
- Value类： `value.h` `value.cpp`
- 类型类： `xxx.h` `xxx.cpp`
- 类型转换





### 操作符的调用栈

![image-20241020134929936](https://my-pic.miaops.sbs/2024/10/image-20241020134929936.png)



![image-20241020134834906](https://my-pic.miaops.sbs/2024/10/image-20241020134834906.png)

RC ComparisonExpr::compare_column

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)



`RC ComparisonExpr::compare_value`

RC ComparisonExpr::get_value

RC TableScanVecPhysicalOperator::filter(Chunk &chunk)

RC TableScanVecPhysicalOperator::next(Chunk &chunk)



RC SqlResult::next_chunk(Chunk &chunk)   `next_tuple`

RC PlainCommunicator::write_chunk_result(SqlResult *sql_result)  `write_tuple_result`

RC PlainCommunicator::write_result_internal(SessionEvent *event, bool &need_disconnect)

RC PlainCommunicator::write_result(SessionEvent *event, bool &need_disconnect)

TableGetLogicalOperator走的是TableScanPhysicalOperator

