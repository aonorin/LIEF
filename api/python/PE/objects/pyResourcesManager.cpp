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
#include "pyPE.hpp"

#include "LIEF/visitors/Hash.hpp"
#include "LIEF/PE/ResourcesManager.hpp"

#include <string>
#include <sstream>


template<class T>
using getter_t = T (ResourcesManager::*)(void) const;

template<class T>
using setter_t = void (ResourcesManager::*)(T);

template<class T, class P>
using no_const_func = T (ResourcesManager::*)(P);

void init_PE_ResourcesManager_class(py::module& m) {
  py::class_<ResourcesManager>(m, "ResourcesManager",
      "The Resource Manager provides an enhanced API to manipulate the resource tree")

    .def_property_readonly("has_manifest",
        &ResourcesManager::has_manifest,
        "``True`` if resources contain Manifest element")

    .def_property("manifest",
        static_cast<getter_t<std::string>>(&ResourcesManager::manifest),
        static_cast<setter_t<const std::string&>>(&ResourcesManager::manifest),
        "Manifest as a ``string``")


    .def_property_readonly("has_version",
        &ResourcesManager::has_version,
        "``true`` if resources contain " RST_CLASS_REF(lief.PE.ResourceVersion) "")

    .def_property_readonly("version",
        static_cast<getter_t<ResourceVersion>>(&ResourcesManager::version),
        "Return the " RST_CLASS_REF(lief.PE.ResourceVersion) "")
        //static_cast<setter_t<const ResourceVersion&>>(&ResourcesManager::version))


    .def_property_readonly("has_icons",
        &ResourcesManager::has_icons,
        "``true`` if resources contain " RST_CLASS_REF(lief.PE.ResourceIcon) "")

    .def_property_readonly("icons",
      &ResourcesManager::icons,
      "Return the list of the " RST_CLASS_REF(lief.PE.ResourceIcon) " present in the resource")

    .def("change_icon",
        &ResourcesManager::change_icon,
        "Switch the given icons",
        "old_one"_a, "new_one"_a)

    .def_property_readonly("has_dialogs",
        &ResourcesManager::has_dialogs,
        "``true`` if resources contain " RST_CLASS_REF(lief.PE.ResourceDialog) "")

    .def_property_readonly("dialogs",
      &ResourcesManager::dialogs,
      "Return the list of the " RST_CLASS_REF(lief.PE.ResourceDialog) " present in the resource")

    .def_property_readonly("types_available",
      &ResourcesManager::get_types_available,
      "Return list of " RST_CLASS_REF(lief.PE.RESOURCE_TYPES) " present in the resources")

    .def_property_readonly("langs_available",
      &ResourcesManager::get_langs_available,
      "Return list of " RST_CLASS_REF(lief.PE.RESOURCE_LANGS) " present in the resources")

    .def_property_readonly("sublangs_available",
      &ResourcesManager::get_sublangs_available,
      "Return list of " RST_CLASS_REF(lief.PE.RESOURCE_SUBLANGS) " present in the resources")

    .def("add_icon",
      &ResourcesManager::add_icon,
      "Add an icon to the resources",
      "icon"_a)

    .def("has_type",
      &ResourcesManager::has_type,
      "``True`` if the resource has the given " RST_CLASS_REF(lief.PE.RESOURCE_TYPES) "",
      "type"_a)

    .def("get_node_type",
      static_cast<no_const_func<ResourceNode&, RESOURCE_TYPES>>(&ResourcesManager::get_node_type),
      "Return " RST_CLASS_REF(lief.PE.ResourceNode) " with "
      "the given " RST_CLASS_REF(lief.PE.RESOURCE_TYPES) "",
      "type"_a,
      py::return_value_policy::reference)

    .def("__str__",
        [] (const ResourcesManager& manager) {
          std::ostringstream stream;
          stream << manager;
          std::string str = stream.str();
          return str;
        });
}

