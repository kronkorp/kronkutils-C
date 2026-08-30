file(REMOVE_RECURSE
  "libkronkutils.pdb"
  "libkronkutils.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/kronkutils_shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
