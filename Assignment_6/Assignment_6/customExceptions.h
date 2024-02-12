#pragma once
#include <exception>
#include <string>

using namespace std;


class CustomException : public std::exception {
protected:

    std::string message;

public:

    explicit CustomException(string exceptionMessage);

    const char* what() const noexcept override;
};

class ValidatorException : public CustomException {
public:

    explicit ValidatorException(string exceptionMessage);
};

class RepositoryException : public CustomException {
public:

    explicit RepositoryException(string exceptionMessage);
};