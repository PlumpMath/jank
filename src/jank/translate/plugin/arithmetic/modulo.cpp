#include <jank/parse/expect/type.hpp>
#include <jank/translate/plugin/arithmetic/modulo.hpp>
#include <jank/translate/plugin/arithmetic/detail/make_operator.hpp>
#include <jank/interpret/environment/resolve_value.hpp>

namespace jank
{
  namespace translate
  {
    namespace plugin
    {
      namespace arithmetic
      {
        /* TODO: Handle modulo by zero. */
        void modulo(std::shared_ptr<environment::scope> const &scope)
        {
          detail::make_operator
          (
            scope, "%", environment::builtin::type::integer(*scope),
            [](auto const &scope, auto const &args)
            {
              auto ret
              (
                parse::expect::type<parse::cell::type::integer>
                (interpret::resolve_value(scope, args[0].cell)).data
              );
              ret %= parse::expect::type<parse::cell::type::integer>
              (interpret::resolve_value(scope, args[1].cell)).data;
              return environment::builtin::value::integer(ret);
            }
          );
        }
      }
    }
  }
}