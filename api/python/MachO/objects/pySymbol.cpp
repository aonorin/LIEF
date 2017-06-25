/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string>
#include <sstream>

#include "LIEF/visitors/Hash.hpp"
#include "LIEF/MachO/Section.hpp"

#include "pyMachO.hpp"


template<class T>
using getter_t = T (Symbol::*)(void) const;

template<class T>
using setter_t = void (Symbol::*)(T);

void init_MachO_Symbol_class(py::module& m) {

  py::class_<Symbol, LIEF::Symbol>(m, "Symbol")
    .def(py::init<>())

    .def_property_readonly("demangled_name",
        &Symbol::demangled_name,
        "Symbol's unmangled name")

    .def_property("type",
        static_cast<getter_t<uint8_t>>(&Symbol::type),
        static_cast<setter_t<uint8_t>>(&Symbol::type))

    .def_property("numberof_sections",
        static_cast<getter_t<uint8_t>>(&Symbol::numberof_sections),
        static_cast<setter_t<uint8_t>>(&Symbol::numberof_sections))

    .def_property("description",
        static_cast<getter_t<uint16_t>>(&Symbol::description),
        static_cast<setter_t<uint16_t>>(&Symbol::description))

    .def_property("value",
        static_cast<getter_t<uint64_t>>(&Symbol::value),
        static_cast<setter_t<uint64_t>>(&Symbol::value))

    .def("__eq__", &Symbol::operator==)
    .def("__ne__", &Symbol::operator!=)
    .def("__hash__",
        [] (const Symbol& symbol) {
          return LIEF::Hash::hash(symbol);
        })


    .def("__str__",
        [] (const Symbol& symbol)
        {
          std::ostringstream stream;
          stream << symbol;
          std::string str =  stream.str();
          return str;
        });

}



