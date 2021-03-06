(ns jank.type.scope.type-definition
  (:require [jank.type.scope.type-declaration :as type-declaration]
            [jank.type.scope.util :as util])
  (:use clojure.walk
        jank.assert
        jank.debug.log))

; Look up based on type, returning full definition
(def lookup (partial util/lookup
                     (fn [v m]
                       (some #(when (= (:type %) v)
                                %)
                             (:type-definitions m)))))

(defn add-to-scope
  [item scope]
  (internal-assert (some? (:type item))
                   (str "item has no type " item))
  (let [with-decl (type-declaration/add-to-scope item scope)]
    (update with-decl :type-definitions conj item)))
