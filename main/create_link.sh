if [ "$HOSTTYPE" == '' ]; then
HOSTTYPE="$(shell uname -m)_$(shell uname -s)"
fi

ln -fs libft_malloc.so "libft_malloc_$HOSTTYPE.so"