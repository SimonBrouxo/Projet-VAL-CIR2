# CMakeList.txt : projet CMake pour Projet-VAL-CIR2, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (Projet-VAL-CIR2 "Projet-VAL-CIR2.cpp" "Projet-VAL-CIR2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Projet-VAL-CIR2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
