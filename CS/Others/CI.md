Visitor**访问模式代码示例**：

具体讲解：==P88== ==P90==

本质：让OOP带有FP特点，采用基类作为中间层。

```java
	package lox;

// 抽象基类：所有表达式的父类
abstract class Expr {
    interface Visitor<R> {
        R visitBinaryExpr(Binary expr);
        R visitUnaryExpr(Unary expr);
        R visitLiteralExpr(Literal expr);
        R visitGroupingExpr(Grouping expr);
    }

    // 二元表达式（如 a + b）
    static class Binary extends Expr {
        final Expr left;
        final Token operator;
        final Expr right;

        Binary(Expr left, Token operator, Expr right) {
            this.left = left;
            this.operator = operator;
            this.right = right;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
            return visitor.visitBinaryExpr(this);
        }
    }

    // 一元表达式（如 -a）
    static class Unary extends Expr {
        final Token operator;
        final Expr right;

        Unary(Token operator, Expr right) {
            this.operator = operator;
            this.right = right;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
            return visitor.visitUnaryExpr(this);
        }
    }

    // 字面量表达式（如 123, "hello"）
    static class Literal extends Expr {
        final Object value;

        Literal(Object value) {
            this.value = value;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
            return visitor.visitLiteralExpr(this);
        }
    }

    // 括号表达式（如 (a + b)）
    static class Grouping extends Expr {
        final Expr expression;

        Grouping(Expr expression) {
            this.expression = expression;
        }

        @Override
        <R> R accept(Visitor<R> visitor) {
            return visitor.visitGroupingExpr(this);
        }
    }

    // 访问者模式：用于遍历 AST
    abstract <R> R accept(Visitor<R> visitor);
}

```



```java
package lox;

import java.util.Arrays;
import java.util.List;

class AstPrinter implements Expr.Visitor<String> {

    public static void main(String[] args) {
        // 构建不同类型的Expr
        Expr literal = new Expr.Literal(123);
        Expr.Unary unary = new Expr.Unary(new Token(TokenType.MINUS, "-", null, 1), literal);
        Expr expression = new Expr.Binary(
                unary,
                new Token(TokenType.STAR, "*", null, 1),
                new Expr.Literal(45.67)
        );
        List<Expr> exprList = Arrays.asList(literal, unary, expression);

        // 打印 AST
        AstPrinter printer = new AstPrinter();
        for (Expr expr : exprList) {
            System.out.println(expr.accept(printer)); // !!!
        }
    }

    @Override
    public String visitBinaryExpr(Expr.Binary expr) {
        return parenthesize(expr.operator.lexeme, expr.left, expr.right);
    }

    @Override
    public String visitUnaryExpr(Expr.Unary expr) {
        return parenthesize(expr.operator.lexeme, expr.right);
    }

    @Override
    public String visitLiteralExpr(Expr.Literal expr) {
        return expr.value == null ? "nil" : expr.value.toString();
    }

    @Override
    public String visitGroupingExpr(Expr.Grouping expr) {
        return parenthesize("group", expr.expression);
    }

    private String parenthesize(String name, Expr... exprs) {
        StringBuilder builder = new StringBuilder();
        builder.append("(").append(name);
        for (Expr expr : exprs) {
            builder.append(" ").append(expr.accept(this)); // !!!
        }
        builder.append(")");
        return builder.toString();
    }
}
```





