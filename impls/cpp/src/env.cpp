#include "../headers/env.hpp"

std::optional<mal::Type*>
mal::get_env(env_t &env, std::string const &key) {
    auto it = env.find(key);

    if ( it == env.end() )
        return {};
    return it->second;
}

void
mal::set_env(env_t &env, std::string const &key, Type *value) {
    env.insert(std::make_pair(key, value));
}

// Env exception

mal::EnvException::EnvException(std::string const &msg) :
    m_msg("env: " + msg) { }

char const*
mal::EnvException::what() const throw() {
    return m_msg.c_str();
}

mal::EnvNotFoundException::EnvNotFoundException(std::string const &key) :
    mal::EnvException("symbol " + key + " not found in environment") { }

char const*
mal::EnvNotFoundException::what() const throw() {
    return mal::EnvException::what();
}