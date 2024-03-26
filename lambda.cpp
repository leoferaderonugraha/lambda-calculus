#include "lambda.h"
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>


Variable* generate_random_var() {
    static int current = 0;
    const char* alphabets = "abcdefghijklmnopqrstuvwxyz";

    if (current > 25) {
        current = 0;
    }

    return new Variable(alphabets[current++]);
}


bool is_expr_equal(LambdaExpr* expr1, LambdaExpr* expr2) {
    return expr1->to_str() == expr2->to_str();
}


Variable::Variable(char value)
    : m_value(value){};

std::string Variable::to_str() {
    std::stringstream ss;

    ss << m_value;

    return ss.str();
}

bool Variable::is_variable() {
    return true;
}

Variable* Variable::evaluate() {
    return this;
}

char Variable::get_value() {
    return m_value;
}

void Variable::set_value(char value) {
    m_value = value;
}


Abstraction::Abstraction(LambdaExpr* lparam, LambdaExpr* rparam)
    : m_lparam(lparam), m_rparam(rparam){};

std::string Abstraction::to_str() {
    std::stringstream ss;

    ss << "!" << m_lparam->to_str() << "." << m_rparam->to_str();

    return ss.str();
}

LambdaExpr* Abstraction::get_lparam() {
    return m_lparam;
}

LambdaExpr* Abstraction::get_rparam() {
    return m_rparam;
}

void Abstraction::set_lparam(LambdaExpr* param) {
    m_lparam = param;
}

void Abstraction::set_rparam(LambdaExpr* param) {
    m_rparam = param;
}

bool Abstraction::is_abstraction() {
    return true;
}

Abstraction* Abstraction::evaluate() {
    return this;
}


Application::Application(LambdaExpr* lparam, LambdaExpr* rparam)
    : m_lparam(lparam), m_rparam(rparam){};

LambdaExpr* Application::get_lparam() {
    return m_lparam;
}

LambdaExpr* Application::get_rparam() {
    return m_rparam;
}

std::string Application::to_str() {
    std::stringstream ss;

    ss << m_lparam->to_str();

    if (m_rparam != nullptr) {
        ss << " " << m_rparam->to_str();
    }

    return ss.str();
}

bool Application::is_application() {
    return true;
}

Application* Application::evaluate() {
    if (m_rparam == nullptr) {
        return this;
    }

    if (m_lparam->is_variable()) {
        return this;
    } else if (m_lparam->is_abstraction()) {
        // TODO:
        // - Support Application
        if (m_rparam->is_variable()) {
            // only support call by variable by now
            if (m_lparam->get_rparam()->is_variable()) {
                // Abstraction with a body of a variable
                if (is_expr_equal(m_lparam->get_lparam(), m_lparam->get_rparam())) {
                    return new Application(m_rparam, nullptr);
                } else {
                    m_rparam = nullptr;
                    return this;
                }
            } else if (m_lparam->get_rparam()->is_abstraction()) {
                LambdaExpr* outer_param = m_lparam->get_lparam();
                LambdaExpr* abstract_param = m_lparam->get_rparam();

                while (abstract_param->is_abstraction()) {
                    // rename param
                    if (is_expr_equal(outer_param, abstract_param->get_lparam())) {
                        LambdaExpr* var = generate_random_var();

                        while (is_expr_equal(var, abstract_param->get_rparam())) {
                            var = generate_random_var();
                        }

                        if (abstract_param->get_rparam()->is_variable() &&
                            is_expr_equal(abstract_param->get_lparam(), abstract_param->get_rparam())) {
                                abstract_param->set_rparam(var);
                        }
                        abstract_param->set_lparam(var);
                    }

                    abstract_param = abstract_param->get_rparam();
                }

                // last node, should be a variable by then
                if (is_expr_equal(outer_param, abstract_param)) {
                    abstract_param->set_value(m_rparam->get_value());
                }

                m_rparam = nullptr;
                m_lparam = m_lparam->get_rparam();

                return this;
            }
        }
    }

    return this;
}
