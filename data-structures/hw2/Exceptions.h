//
// Created by noam on 12/31/17.
//

#ifndef HW_WET2_EXCEPTIONS_H
#define HW_WET2_EXCEPTIONS_H


#include <exception>

namespace ds_exceptions {
    class NodeIsAlreadyExistException : public std::exception{};
    class NotEnoughNodesException : public std::exception{};
    class InvalidInputException : public std::exception{};
    class FailureException : public std::exception{};
}

#endif //HW_WET2_EXCEPTIONS_H
