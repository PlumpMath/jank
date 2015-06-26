#pragma once

#include <jank/parse/cell/cell.hpp>
#include <jank/translate/cell/cell.hpp>
#include <jank/interpret/environment/scope.hpp>

namespace jank
{
  namespace interpret
  {
    parse::cell::cell resolve_value
    (
      std::shared_ptr<environment::scope> const &scope,
      translate::cell::cell const &c
    );
  }
}