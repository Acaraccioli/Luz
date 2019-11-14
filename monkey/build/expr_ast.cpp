/* expr_ast.cpp.  Generated automatically by treecc */
#line 15 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"

    #include "expr_ast.h"
    #include <stdio.h>
    #include <iostream>
    void yyerror(const char *msg);
    std::unordered_map<std::string, int> idents;

#line 11 "expr_ast.cpp"

#define YYNODESTATE_REENTRANT 1
#define YYNODESTATE_TRACK_LINES 1
#define YYNODESTATE_USE_ALLOCATOR 1
#line 1 "cpp_skel.cc"
/*
 * treecc node allocation routines for C++.
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * As a special exception, when this file is copied by treecc into
 * a treecc output file, you may use that output file without restriction.
 */

#ifndef YYNODESTATE_BLKSIZ
#define	YYNODESTATE_BLKSIZ	2048
#endif

/*
 * Types used by the allocation routines.
 */
struct YYNODESTATE_block
{
	char data__[YYNODESTATE_BLKSIZ];
	struct YYNODESTATE_block *next__;

};
struct YYNODESTATE_push
{
	struct YYNODESTATE_push *next__;
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
};

/*
 * Initialize the singleton instance.
 */
#ifndef YYNODESTATE_REENTRANT
YYNODESTATE *YYNODESTATE::state__ = 0;
#endif

/*
 * Some macro magic to determine the default alignment
 * on this machine.  This will compile down to a constant.
 */
#define	YYNODESTATE_ALIGN_CHECK_TYPE(type,name)	\
	struct _YYNODESTATE_align_##name { \
		char pad; \
		type field; \
	}
#define	YYNODESTATE_ALIGN_FOR_TYPE(type)	\
	((unsigned)(unsigned long)(&(((struct _YYNODESTATE_align_##type *)0)->field)))
#define	YYNODESTATE_ALIGN_MAX(a,b)	\
	((a) > (b) ? (a) : (b))
#define	YYNODESTATE_ALIGN_MAX3(a,b,c) \
	(YYNODESTATE_ALIGN_MAX((a), YYNODESTATE_ALIGN_MAX((b), (c))))
YYNODESTATE_ALIGN_CHECK_TYPE(int, int);
YYNODESTATE_ALIGN_CHECK_TYPE(long, long);
#if defined(WIN32) && !defined(__CYGWIN__)
YYNODESTATE_ALIGN_CHECK_TYPE(__int64, long_long);
#else
YYNODESTATE_ALIGN_CHECK_TYPE(long long, long_long);
#endif
YYNODESTATE_ALIGN_CHECK_TYPE(void *, void_p);
YYNODESTATE_ALIGN_CHECK_TYPE(float, float);
YYNODESTATE_ALIGN_CHECK_TYPE(double, double);
#define	YYNODESTATE_ALIGNMENT	\
	YYNODESTATE_ALIGN_MAX( \
			YYNODESTATE_ALIGN_MAX3	\
			(YYNODESTATE_ALIGN_FOR_TYPE(int), \
		     YYNODESTATE_ALIGN_FOR_TYPE(long), \
			 YYNODESTATE_ALIGN_FOR_TYPE(long_long)), \
  	     YYNODESTATE_ALIGN_MAX3 \
		 	(YYNODESTATE_ALIGN_FOR_TYPE(void_p), \
			 YYNODESTATE_ALIGN_FOR_TYPE(float), \
			 YYNODESTATE_ALIGN_FOR_TYPE(double)))

/*
 * Constructor for YYNODESTATE.
 */
YYNODESTATE::YYNODESTATE()
{
	/* Initialize the allocation state */
	blocks__ = 0;
	push_stack__ = 0;
	used__ = 0;

#ifndef YYNODESTATE_REENTRANT
	/* Register this object as the singleton instance */
	if(!state__)
	{
		state__ = this;
	}
#endif
}

/*
 * Destructor for YYNODESTATE.
 */
YYNODESTATE::~YYNODESTATE()
{
	/* Free all node memory */
	clear();

#ifndef YYNODESTATE_REENTRANT
	/* We are no longer the singleton instance */
	if(state__ == this)
	{
		state__ = 0;
	}
#endif
}

#ifdef YYNODESTATE_USE_ALLOCATOR

/*
 * Allocate a block of memory.
 */
void *YYNODESTATE::alloc(size_t size__)
{
	struct YYNODESTATE_block *block__;
	void *result__;

	/* Round the size to the next alignment boundary */
	size__ = (size__ + YYNODESTATE_ALIGNMENT - 1) &
				~(YYNODESTATE_ALIGNMENT - 1);

	/* Do we need to allocate a new block? */
	block__ = blocks__;
	if(!block__ || (used__ + size__) > YYNODESTATE_BLKSIZ)
	{
		if(size__ > YYNODESTATE_BLKSIZ)
		{
			/* The allocation is too big for the node pool */
			return (void *)0;
		}
		block__ = new YYNODESTATE_block;
		if(!block__)
		{
			/* The system is out of memory.  The programmer can
			   inherit the "failed" method to report the
			   out of memory state and/or abort the program */
			failed();
			return (void *)0;
		}
		block__->next__ = blocks__;
		blocks__ = block__;
		used__ = 0;
	}

	/* Allocate the memory and return it */
	result__ = (void *)(block__->data__ + used__);
	used__ += size__;
	return result__;
}

/*
 * Deallocate a block of memory.
 */
void YYNODESTATE::dealloc(void *ptr__, size_t size__)
{
	/* Nothing to do for this type of node allocator */
}

/*
 * Push the node allocation state.
 */
int YYNODESTATE::push()
{
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
	struct YYNODESTATE_push *push_item__;

	/* Save the current state of the node allocation pool */
	saved_block__ = blocks__;
	saved_used__ = used__;

	/* Allocate space for a push item */
	push_item__ = (struct YYNODESTATE_push *)
			alloc(sizeof(struct YYNODESTATE_push));
	if(!push_item__)
	{
		return 0;
	}

	/* Copy the saved information to the push item */
	push_item__->saved_block__ = saved_block__;
	push_item__->saved_used__ = saved_used__;

	/* Add the push item to the push stack */
	push_item__->next__ = push_stack__;
	push_stack__ = push_item__;
	return 1;
}

/*
 * Pop the node allocation state.
 */
void YYNODESTATE::pop()
{
	struct YYNODESTATE_push *push_item__;
	struct YYNODESTATE_block *saved_block__;
	struct YYNODESTATE_block *temp_block__;

	/* Pop the top of the push stack */
	push_item__ = push_stack__;
	if(push_item__ == 0)
	{
		saved_block__ = 0;
		used__ = 0;
	}
	else
	{
		saved_block__ = push_item__->saved_block__;
		used__ = push_item__->saved_used__;
		push_stack__ = push_item__->next__;
	}

	/* Free unnecessary blocks */
	while(blocks__ != saved_block__)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
}

/*
 * Clear the node allocation pool completely.
 */
void YYNODESTATE::clear()
{
	struct YYNODESTATE_block *temp_block__;
	while(blocks__ != 0)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
	push_stack__ = 0;
	used__ = 0;
}

#endif /* YYNODESTATE_USE_ALLOCATOR */

/*
 * Default implementation of functions which may be overridden.
 */
void YYNODESTATE::failed()
{
}

#ifdef YYNODESTATE_TRACK_LINES

char *YYNODESTATE::currFilename()
{
	return (char *)0;
}

long YYNODESTATE::currLinenum()
{
	return 0;
}

#endif
#line 291 "expr_ast.cpp"
intnum *YYNODESTATE::intnumCreate(int num)
{
	void *buf__ = this->alloc(sizeof(intnum));
	if(buf__ == 0) return 0;
	return new (buf__) intnum(this, num);
}

floatnum *YYNODESTATE::floatnumCreate(float num)
{
	void *buf__ = this->alloc(sizeof(floatnum));
	if(buf__ == 0) return 0;
	return new (buf__) floatnum(this, num);
}

identifier *YYNODESTATE::identifierCreate(string_t id_string)
{
	void *buf__ = this->alloc(sizeof(identifier));
	if(buf__ == 0) return 0;
	return new (buf__) identifier(this, id_string);
}

plus *YYNODESTATE::plusCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(plus));
	if(buf__ == 0) return 0;
	return new (buf__) plus(this, expr1, expr2);
}

minus *YYNODESTATE::minusCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(minus));
	if(buf__ == 0) return 0;
	return new (buf__) minus(this, expr1, expr2);
}

multiply *YYNODESTATE::multiplyCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(multiply));
	if(buf__ == 0) return 0;
	return new (buf__) multiply(this, expr1, expr2);
}

divide *YYNODESTATE::divideCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(divide));
	if(buf__ == 0) return 0;
	return new (buf__) divide(this, expr1, expr2);
}

equal *YYNODESTATE::equalCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(equal));
	if(buf__ == 0) return 0;
	return new (buf__) equal(this, expr1, expr2);
}

notequal *YYNODESTATE::notequalCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(notequal));
	if(buf__ == 0) return 0;
	return new (buf__) notequal(this, expr1, expr2);
}

lessthan *YYNODESTATE::lessthanCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(lessthan));
	if(buf__ == 0) return 0;
	return new (buf__) lessthan(this, expr1, expr2);
}

greaterthan *YYNODESTATE::greaterthanCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(greaterthan));
	if(buf__ == 0) return 0;
	return new (buf__) greaterthan(this, expr1, expr2);
}

lessthanorequal *YYNODESTATE::lessthanorequalCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(lessthanorequal));
	if(buf__ == 0) return 0;
	return new (buf__) lessthanorequal(this, expr1, expr2);
}

greaterthanorequal *YYNODESTATE::greaterthanorequalCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(greaterthanorequal));
	if(buf__ == 0) return 0;
	return new (buf__) greaterthanorequal(this, expr1, expr2);
}

power *YYNODESTATE::powerCreate(ASTNode * expr1, ASTNode * expr2)
{
	void *buf__ = this->alloc(sizeof(power));
	if(buf__ == 0) return 0;
	return new (buf__) power(this, expr1, expr2);
}

negate *YYNODESTATE::negateCreate(ASTNode * expr)
{
	void *buf__ = this->alloc(sizeof(negate));
	if(buf__ == 0) return 0;
	return new (buf__) negate(this, expr);
}

ifStmt *YYNODESTATE::ifStmtCreate(ASTNode * condicion, ASTNode * verdadero, ASTNode * falso)
{
	void *buf__ = this->alloc(sizeof(ifStmt));
	if(buf__ == 0) return 0;
	return new (buf__) ifStmt(this, condicion, verdadero, falso);
}

assign *YYNODESTATE::assignCreate(string_t id, ASTNode * value)
{
	void *buf__ = this->alloc(sizeof(assign));
	if(buf__ == 0) return 0;
	return new (buf__) assign(this, id, value);
}

whileStmt *YYNODESTATE::whileStmtCreate(ASTNode * condicion, ASTNode * action)
{
	void *buf__ = this->alloc(sizeof(whileStmt));
	if(buf__ == 0) return 0;
	return new (buf__) whileStmt(this, condicion, action);
}

blockStmt *YYNODESTATE::blockStmtCreate(ASTNode * first, ASTNode * next)
{
	void *buf__ = this->alloc(sizeof(blockStmt));
	if(buf__ == 0) return 0;
	return new (buf__) blockStmt(this, first, next);
}

print *YYNODESTATE::printCreate(ASTNode * expr)
{
	void *buf__ = this->alloc(sizeof(print));
	if(buf__ == 0) return 0;
	return new (buf__) print(this, expr);
}

ASTNode::ASTNode(YYNODESTATE *state__)
{
	this->kind__ = ASTNode_kind;
	this->filename__ = state__->currFilename();
	this->linenum__ = state__->currLinenum();
}

ASTNode::~ASTNode()
{
	// not used
}

int ASTNode::isA(int kind) const
{
	if(kind == ASTNode_kind)
		return 1;
	else
		return 0;
}

const char *ASTNode::getKindName() const
{
	return "ASTNode";
}

expression::expression(YYNODESTATE *state__)
	: ASTNode(state__)
{
	this->kind__ = expression_kind;
	this->type = int_type;
}

expression::~expression()
{
	// not used
}

int expression::isA(int kind) const
{
	if(kind == expression_kind)
		return 1;
	else
		return ASTNode::isA(kind);
}

const char *expression::getKindName() const
{
	return "expression";
}

statement::statement(YYNODESTATE *state__)
	: ASTNode(state__)
{
	this->kind__ = statement_kind;
}

statement::~statement()
{
	// not used
}

int statement::isA(int kind) const
{
	if(kind == statement_kind)
		return 1;
	else
		return ASTNode::isA(kind);
}

const char *statement::getKindName() const
{
	return "statement";
}

binary::binary(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: expression(state__)
{
	this->kind__ = binary_kind;
	this->expr1 = expr1;
	this->expr2 = expr2;
}

binary::~binary()
{
	// not used
}

int binary::isA(int kind) const
{
	if(kind == binary_kind)
		return 1;
	else
		return expression::isA(kind);
}

const char *binary::getKindName() const
{
	return "binary";
}

unary::unary(YYNODESTATE *state__, ASTNode * expr)
	: expression(state__)
{
	this->kind__ = unary_kind;
	this->expr = expr;
}

unary::~unary()
{
	// not used
}

int unary::isA(int kind) const
{
	if(kind == unary_kind)
		return 1;
	else
		return expression::isA(kind);
}

const char *unary::getKindName() const
{
	return "unary";
}

intnum::intnum(YYNODESTATE *state__, int num)
	: expression(state__)
{
	this->kind__ = intnum_kind;
	this->num = num;
}

intnum::~intnum()
{
	// not used
}

int intnum::eval()
{
	intnum *e = this;
#line 190 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return num;
	}
#line 576 "expr_ast.cpp"
}

int intnum::isA(int kind) const
{
	if(kind == intnum_kind)
		return 1;
	else
		return expression::isA(kind);
}

const char *intnum::getKindName() const
{
	return "intnum";
}

floatnum::floatnum(YYNODESTATE *state__, float num)
	: expression(state__)
{
	this->kind__ = floatnum_kind;
	this->num = num;
}

floatnum::~floatnum()
{
	// not used
}

int floatnum::eval()
{
	floatnum *e = this;
#line 194 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return num;
	}
#line 611 "expr_ast.cpp"
}

int floatnum::isA(int kind) const
{
	if(kind == floatnum_kind)
		return 1;
	else
		return expression::isA(kind);
}

const char *floatnum::getKindName() const
{
	return "floatnum";
}

identifier::identifier(YYNODESTATE *state__, string_t id_string)
	: expression(state__)
{
	this->kind__ = identifier_kind;
	this->id_string = id_string;
}

identifier::~identifier()
{
	// not used
}

int identifier::eval()
{
	identifier *e = this;
#line 186 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return idents[id_string];
	}
#line 646 "expr_ast.cpp"
}

int identifier::isA(int kind) const
{
	if(kind == identifier_kind)
		return 1;
	else
		return expression::isA(kind);
}

const char *identifier::getKindName() const
{
	return "identifier";
}

plus::plus(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = plus_kind;
}

plus::~plus()
{
	// not used
}

int plus::eval()
{
	plus *e = this;
#line 162 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() + expr2->eval();
	}
#line 680 "expr_ast.cpp"
}

int plus::isA(int kind) const
{
	if(kind == plus_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *plus::getKindName() const
{
	return "plus";
}

minus::minus(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = minus_kind;
}

minus::~minus()
{
	// not used
}

int minus::eval()
{
	minus *e = this;
#line 166 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() - expr2->eval();
	}
#line 714 "expr_ast.cpp"
}

int minus::isA(int kind) const
{
	if(kind == minus_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *minus::getKindName() const
{
	return "minus";
}

multiply::multiply(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = multiply_kind;
}

multiply::~multiply()
{
	// not used
}

int multiply::eval()
{
	multiply *e = this;
#line 170 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() * expr2->eval();
	}
#line 748 "expr_ast.cpp"
}

int multiply::isA(int kind) const
{
	if(kind == multiply_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *multiply::getKindName() const
{
	return "multiply";
}

divide::divide(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = divide_kind;
}

divide::~divide()
{
	// not used
}

int divide::eval()
{
	divide *e = this;
#line 174 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() / expr2->eval();
	}
#line 782 "expr_ast.cpp"
}

int divide::isA(int kind) const
{
	if(kind == divide_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *divide::getKindName() const
{
	return "divide";
}

equal::equal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = equal_kind;
}

equal::~equal()
{
	// not used
}

int equal::eval()
{
	equal *e = this;
#line 198 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() == expr2->eval();
	}
#line 816 "expr_ast.cpp"
}

int equal::isA(int kind) const
{
	if(kind == equal_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *equal::getKindName() const
{
	return "equal";
}

notequal::notequal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = notequal_kind;
}

notequal::~notequal()
{
	// not used
}

int notequal::eval()
{
	notequal *e = this;
#line 202 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() != expr2->eval();
	}
#line 850 "expr_ast.cpp"
}

int notequal::isA(int kind) const
{
	if(kind == notequal_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *notequal::getKindName() const
{
	return "notequal";
}

lessthan::lessthan(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = lessthan_kind;
}

lessthan::~lessthan()
{
	// not used
}

int lessthan::eval()
{
	lessthan *e = this;
#line 206 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() < expr2->eval();
	}
#line 884 "expr_ast.cpp"
}

int lessthan::isA(int kind) const
{
	if(kind == lessthan_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *lessthan::getKindName() const
{
	return "lessthan";
}

greaterthan::greaterthan(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = greaterthan_kind;
}

greaterthan::~greaterthan()
{
	// not used
}

int greaterthan::eval()
{
	greaterthan *e = this;
#line 210 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() > expr2->eval();
	}
#line 918 "expr_ast.cpp"
}

int greaterthan::isA(int kind) const
{
	if(kind == greaterthan_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *greaterthan::getKindName() const
{
	return "greaterthan";
}

lessthanorequal::lessthanorequal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = lessthanorequal_kind;
}

lessthanorequal::~lessthanorequal()
{
	// not used
}

int lessthanorequal::eval()
{
	lessthanorequal *e = this;
#line 214 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() <= expr2->eval();
	}
#line 952 "expr_ast.cpp"
}

int lessthanorequal::isA(int kind) const
{
	if(kind == lessthanorequal_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *lessthanorequal::getKindName() const
{
	return "lessthanorequal";
}

greaterthanorequal::greaterthanorequal(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = greaterthanorequal_kind;
}

greaterthanorequal::~greaterthanorequal()
{
	// not used
}

int greaterthanorequal::eval()
{
	greaterthanorequal *e = this;
#line 218 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr1->eval() >= expr2->eval();
	}
#line 986 "expr_ast.cpp"
}

int greaterthanorequal::isA(int kind) const
{
	if(kind == greaterthanorequal_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *greaterthanorequal::getKindName() const
{
	return "greaterthanorequal";
}

power::power(YYNODESTATE *state__, ASTNode * expr1, ASTNode * expr2)
	: binary(state__, expr1, expr2)
{
	this->kind__ = power_kind;
}

power::~power()
{
	// not used
}

int power::eval()
{
	power *e = this;
#line 178 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return std::pow(expr1->eval(),expr2->eval());
	}
#line 1020 "expr_ast.cpp"
}

int power::isA(int kind) const
{
	if(kind == power_kind)
		return 1;
	else
		return binary::isA(kind);
}

const char *power::getKindName() const
{
	return "power";
}

negate::negate(YYNODESTATE *state__, ASTNode * expr)
	: unary(state__, expr)
{
	this->kind__ = negate_kind;
}

negate::~negate()
{
	// not used
}

int negate::eval()
{
	negate *e = this;
#line 182 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    return expr->eval()*-1;
	}
#line 1054 "expr_ast.cpp"
}

int negate::isA(int kind) const
{
	if(kind == negate_kind)
		return 1;
	else
		return unary::isA(kind);
}

const char *negate::getKindName() const
{
	return "negate";
}

ifStmt::ifStmt(YYNODESTATE *state__, ASTNode * condicion, ASTNode * verdadero, ASTNode * falso)
	: statement(state__)
{
	this->kind__ = ifStmt_kind;
	this->condicion = condicion;
	this->verdadero = verdadero;
	this->falso = falso;
}

ifStmt::~ifStmt()
{
	// not used
}

int ifStmt::eval()
{
	ifStmt *e = this;
#line 134 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    if(condicion->eval()){
	        verdadero->eval();
	    } else {
	        falso->eval();
	    }
	    return 1;
	}
#line 1096 "expr_ast.cpp"
}

int ifStmt::isA(int kind) const
{
	if(kind == ifStmt_kind)
		return 1;
	else
		return statement::isA(kind);
}

const char *ifStmt::getKindName() const
{
	return "ifStmt";
}

assign::assign(YYNODESTATE *state__, string_t id, ASTNode * value)
	: statement(state__)
{
	this->kind__ = assign_kind;
	this->id = id;
	this->value = value;
}

assign::~assign()
{
	// not used
}

int assign::eval()
{
	assign *e = this;
#line 151 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    idents[id] = value->eval();
	    return 1;
	}
#line 1133 "expr_ast.cpp"
}

int assign::isA(int kind) const
{
	if(kind == assign_kind)
		return 1;
	else
		return statement::isA(kind);
}

const char *assign::getKindName() const
{
	return "assign";
}

whileStmt::whileStmt(YYNODESTATE *state__, ASTNode * condicion, ASTNode * action)
	: statement(state__)
{
	this->kind__ = whileStmt_kind;
	this->condicion = condicion;
	this->action = action;
}

whileStmt::~whileStmt()
{
	// not used
}

int whileStmt::eval()
{
	whileStmt *e = this;
#line 143 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    while(condicion->eval()){
	        action->eval();
	        condicion->eval();
	    }
	    return 1;
	}
#line 1173 "expr_ast.cpp"
}

int whileStmt::isA(int kind) const
{
	if(kind == whileStmt_kind)
		return 1;
	else
		return statement::isA(kind);
}

const char *whileStmt::getKindName() const
{
	return "whileStmt";
}

blockStmt::blockStmt(YYNODESTATE *state__, ASTNode * first, ASTNode * next)
	: statement(state__)
{
	this->kind__ = blockStmt_kind;
	this->first = first;
	this->next = next;
}

blockStmt::~blockStmt()
{
	// not used
}

int blockStmt::eval()
{
	blockStmt *e = this;
#line 156 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    first->eval();
	    next->eval();
	    return 1;
	}
#line 1211 "expr_ast.cpp"
}

int blockStmt::isA(int kind) const
{
	if(kind == blockStmt_kind)
		return 1;
	else
		return statement::isA(kind);
}

const char *blockStmt::getKindName() const
{
	return "blockStmt";
}

print::print(YYNODESTATE *state__, ASTNode * expr)
	: statement(state__)
{
	this->kind__ = print_kind;
	this->expr = expr;
}

print::~print()
{
	// not used
}

int print::eval()
{
	print *e = this;
#line 129 "/home/alejandro/Documents/CompiII/treecc/ejemplo1/tests/../ast.tc"
	{
	    std::cout << expr->eval() << std::endl;
	    return 1;
	}
#line 1247 "expr_ast.cpp"
}

int print::isA(int kind) const
{
	if(kind == print_kind)
		return 1;
	else
		return statement::isA(kind);
}

const char *print::getKindName() const
{
	return "print";
}

