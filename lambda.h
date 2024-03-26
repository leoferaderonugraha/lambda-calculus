#ifndef LAMBDA_H

#define LAMBDA_H
#include <string>

class LambdaExpr {
public:
    virtual std::string to_str() = 0;
    virtual LambdaExpr* evaluate() = 0;

    virtual LambdaExpr* get_lparam() {
        return nullptr;
    };

    virtual LambdaExpr* get_rparam() {
        return nullptr;
    };

    virtual char get_value() {
        return '\0';
    }

    virtual void set_lparam(LambdaExpr* param) {};
    virtual void set_rparam(LambdaExpr* param) {};
    virtual void set_value(char value) {};

    virtual bool is_variable() {
        return false;
    }

    virtual bool is_abstraction() {
        return false;
    }

    virtual bool is_application() {
        return false;
    }
};

class Variable : public LambdaExpr {
public:
    Variable(char value);
    char get_value() override;
    virtual void set_value(char value) override;
    std::string to_str() override;
    bool is_variable() override;
    Variable* evaluate() override;
private:
    char m_value;
};

class Abstraction : public LambdaExpr {
public:
    Abstraction(LambdaExpr* lparam, LambdaExpr* rparam);
    LambdaExpr* get_lparam() override;
    LambdaExpr* get_rparam() override;
    void set_lparam(LambdaExpr* param) override;
    void set_rparam(LambdaExpr* param) override;
    std::string to_str() override;
    bool is_abstraction() override;
    Abstraction* evaluate() override;
private:
    LambdaExpr* m_lparam;
    LambdaExpr* m_rparam;
};

class Application : public LambdaExpr {
public:
    Application(LambdaExpr* lparam, LambdaExpr* rparam);
    LambdaExpr* get_lparam() override;
    LambdaExpr* get_rparam() override;
    std::string to_str() override;
    bool is_application() override;
    Application* evaluate() override;
private:
    LambdaExpr* m_lparam;
    LambdaExpr* m_rparam;
};

#endif
