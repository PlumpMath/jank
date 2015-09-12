#pragma once

#include <string>
#include <vector>

#include <jank/translate/type/generic/genericity.hpp>

namespace jank
{
  namespace translate
  {
    namespace cell
    {
      namespace detail
      {
        template <typename C>
        struct member_cell
        {
          std::string name;
          C cell;
        };

        template <typename C>
        struct type_definition
        {
          std::string name;
          translate::type::generic::genericity<type_definition> generics;
          std::vector<std::pair<type_definition<C>, member_cell<C>>> members;
        };

        template <typename C>
        using member = std::pair<type_definition<C>, member_cell<C>>;

        template <typename C>
        bool operator ==
        (type_definition<C> const &lhs, type_definition<C> const &rhs)
        {
          return
          (
            lhs.name == rhs.name &&
            lhs.generics == rhs.generics
          );
        }

        template <typename C>
        bool operator !=
        (type_definition<C> const &lhs, type_definition<C> const &rhs)
        {
          return
          (
            lhs.name != rhs.name ||
            lhs.generics != rhs.generics
          );
        }
      }
    }
  }
}
