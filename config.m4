PHP_ARG_ENABLE(testext, whether to enable test extension,
[ --enable-testext   Enable testext support])

if test "$PHP_TESTEXT" = "yes"; then
  AC_DEFINE(HAVE_TESTEXT, 1, [Whether you have testext])
  PHP_NEW_EXTENSION(testext, testext_obj.c testext.c, $ext_shared)
fi
