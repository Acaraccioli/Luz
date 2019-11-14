/* expr_ast.h.  Generated automatically by treecc */
#ifndef __yy_expr_ast_h
#define __yy_expr_ast_h
#line 4 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"

#include <string>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <cstddef>
using string_t =std::string;


#line 15 "expr_ast.h"

#include <new>

const int ASTNode_kind = 5;
const int expression_kind = 6;
const int statement_kind = 24;
const int binary_kind = 7;
const int unary_kind = 8;
const int intnum_kind = 9;
const int floatnum_kind = 10;
const int identifier_kind = 11;
const int plus_kind = 12;
const int minus_kind = 13;
const int multiply_kind = 14;
const int divide_kind = 15;
const int equal_kind = 16;
const int notequal_kind = 17;
const int lessthan_kind = 18;
const int greaterthan_kind = 19;
const int lessthanorequal_kind = 20;
const int greaterthanorequal_kind = 21;
const int power_kind = 23;
const int negate_kind = 22;
const int ifStmt_kind = 25;
const int assign_kind = 26;
const int whileStmt_kind = 27;
const int blockStmt_kind = 28;
const int print_kind = 29;

class ASTNode;
class expression;
class statement;
class binary;
class unary;
class intnum;
class floatnum;
class identifier;
class plus;
class minus;
class multiply;
class divide;
class equal;
class notequal;
class lessthan;
class greaterthan;
class lessthanorequal;
class greaterthanorequal;
class power;
class negate;
class ifStmt;
class assign;
class whileStmt;
class blockStmt;
class print;
typedef enum {
	int_type,
	float_type,
	string_type,
} type_code;


class YYNODESTATE
{
public:

	YYNODESTATE();
	virtual ~YYNODESTATE();

#line 1 "cpp_skel.h"
private:

	struct YYNODESTATE_block *blocks__;
	struct YYNODESTATE_push *push_stack__;
	int used__;
#line 90 "expr_ast.h"
public:

	intnum *intnumCreate(int num);
	floatnum *floatnumCreate(float num);
	identifier *identifierCreate(string_t id_string);
	plus *plusCreate(ASTNode * expr1, ASTNode * expr2);
	minus *minusCreate(ASTNode * expr1, ASTNode * expr2);
	multiply *multiplyCreate(ASTNode * expr1, ASTNode * expr2);
	divide *divideCreate(ASTNode * expr1, ASTNode * expr2);
	equal *equalCreate(ASTNode * expr1, ASTNode * expr2);
	notequal *notequalCreate(ASTNode * expr1, ASTNode * expr2);
	lessthan *lessthanCreate(ASTNode * expr1, ASTNode * expr2);
	greaterthan *greaterthanCreate(ASTNode * expr1, ASTNode * expr2);
	lessthanorequal *lessthanorequalCreate(ASTNode * expr1, ASTNode * expr2);
	greaterthanorequal *greaterthanorequalCreate(ASTNode * expr1, ASTNode * expr2);
	power *powerCreate(ASTNode * expr1, ASTNode * expr2);
	negate *negateCreate(ASTNode * expr);
	ifStmt *ifStmtCreate(ASTNode * condicion, ASTNode * verdadero, ASTNode * falso);
	assign *assignCreate(string_t id, ASTNode * value);
	whileStmt *whileStmtCreate(ASTNode * condicion, ASTNode * action);
	blockStmt *blockStmtCreate(ASTNode * first, ASTNode * next);
	print *printCreate(ASTNode * expr);

public:

	void *alloc(size_t);
	void dealloc(void *, size_t);
	int push();
	void pop();
	void clear();
	virtual void failed();
	virtual char *currFilename();
	virtual long currLinenum();

};

class ASTNode
{
protected:

	int kind__;
	char *filename__;
	long linenum__;

public:

	int getKind() const { return kind__; }
	const char *getFilename() const { return filename__; }
	long getLinenum() const { return linenum__; }
	void setFilename(char *filename) { filename__ = filename; }
	void setLinenum(long linenum) { linenum__ = linenum; }

protected:

	friend class YYNODESTATE;

	ASTNode(YYNODESTATE *state__);

public:

	virtual int eval() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~ASTNode();

};

class expression : public ASTNode
{
protected:

	friend class YYNODESTATE;

	expression(YYNODESTATE *state__);

public:

	type_code type;

	virtual int eval() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~expression();

};

class statement : public ASTNode
{
protected:

	friend class YYNODESTATE;

	statement(YYNODESTATE *state__);

public:

	virtual int eval() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~statement();

};

class binary : public expression
{
protected:

	friend class YYNODESTATE;

	binary(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	ASTNode * expr1;
	ASTNode * expr2;

	virtual int eval() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~binary();

};

class unary : public expression
{
protected:

	friend class YYNODESTATE;

	unary(YYNODESTATE *state__, ASTNode * expr);

public:

	ASTNode * expr;

	virtual int eval() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~unary();

};

class intnum : public expression
{
protected:

	friend class YYNODESTATE;

	intnum(YYNODESTATE *state__, int num);

public:

	int num;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~intnum();

};

class floatnum : public expression
{
protected:

	friend class YYNODESTATE;

	floatnum(YYNODESTATE *state__, float num);

public:

	float num;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~floatnum();

};

class identifier : public expression
{
protected:

	friend class YYNODESTATE;

	identifier(YYNODESTATE *state__, string_t id_string);

public:

	string_t id_string;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~identifier();

};

class plus : public binary
{
protected:

	friend class YYNODESTATE;

	plus(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~plus();

};

class minus : public binary
{
protected:

	friend class YYNODESTATE;

	minus(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~minus();

};

class multiply : public binary
{
protected:

	friend class YYNODESTATE;

	multiply(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~multiply();

};

class divide : public binary
{
protected:

	friend class YYNODESTATE;

	divide(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~divide();

};

class equal : public binary
{
protected:

	friend class YYNODESTATE;

	equal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~equal();

};

class notequal : public binary
{
protected:

	friend class YYNODESTATE;

	notequal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~notequal();

};

class lessthan : public binary
{
protected:

	friend class YYNODESTATE;

	lessthan(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~lessthan();

};

class greaterthan : public binary
{
protected:

	friend class YYNODESTATE;

	greaterthan(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~greaterthan();

};

class lessthanorequal : public binary
{
protected:

	friend class YYNODESTATE;

	lessthanorequal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~lessthanorequal();

};

class greaterthanorequal : public binary
{
protected:

	friend class YYNODESTATE;

	greaterthanorequal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~greaterthanorequal();

};

class power : public binary
{
protected:

	friend class YYNODESTATE;

	power(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~power();

};

class negate : public unary
{
protected:

	friend class YYNODESTATE;

	negate(YYNODESTATE *state__, ASTNode * expr);

public:

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~negate();

};

class ifStmt : public statement
{
protected:

	friend class YYNODESTATE;

	ifStmt(YYNODESTATE *state__, ASTNode * condicion, ASTNode * verdadero, ASTNode * falso);

public:

	ASTNode * condicion;
	ASTNode * verdadero;
	ASTNode * falso;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~ifStmt();

};

class assign : public statement
{
protected:

	friend class YYNODESTATE;

	assign(YYNODESTATE *state__, string_t id, ASTNode * value);

public:

	string_t id;
	ASTNode * value;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~assign();

};

class whileStmt : public statement
{
protected:

	friend class YYNODESTATE;

	whileStmt(YYNODESTATE *state__, ASTNode * condicion, ASTNode * action);

public:

	ASTNode * condicion;
	ASTNode * action;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~whileStmt();

};

class blockStmt : public statement
{
protected:

	friend class YYNODESTATE;

	blockStmt(YYNODESTATE *state__, ASTNode * first, ASTNode * next);

public:

	ASTNode * first;
	ASTNode * next;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~blockStmt();

};

class print : public statement
{
protected:

	friend class YYNODESTATE;

	print(YYNODESTATE *state__, ASTNode * expr);

public:

	ASTNode * expr;

	virtual int eval();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~print();

};



#endif
