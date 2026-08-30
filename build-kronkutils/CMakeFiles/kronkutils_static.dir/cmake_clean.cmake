file(REMOVE_RECURSE
  "libkronkutils.a"
  "libkronkutils.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/kronkutils_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
