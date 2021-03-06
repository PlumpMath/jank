(ns jank.interpret.escape
  (:require [jank.type.scope.type-declaration :as type-declaration]
            [jank.type.expression :as expression]
            [jank.interpret.macro :as macro])
  (:use jank.assert
        jank.debug.log))

(defn unescape
  "Turns an evaluated AST map with an interpreted value into a syntax item.
   For example, a syntax-escaped call may evaluate to 42, but it will need to be
   wrapped into {:kind :syntax-item :value {:kind :integer :value 42}}
   to be passed back into check shim. This is because escaped syntax items
   are evaluated during unparsing, in the check shim."
  [evaluated]
  (let [item (-> evaluated :cells last)
        item-value (:interpreted-value item)
        item-type (expression/realize-type item (:scope item))
        item-type-name (-> item-type :value :name keyword)]
    (cond
      (= :syntax item-type-name) item-value
      (type-declaration/built-ins item-type-name) {:kind :syntax-item
                                                   :value {:kind item-type-name
                                                           :value item-value}}
      :else (not-yet-implemented type-assert "unescaped user types"))))

(def evaluate (comp unescape macro/evaluate))
