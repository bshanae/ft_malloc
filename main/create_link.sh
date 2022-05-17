if [ "${HOSTTYPE}" == '' ]; then
HOSTTYPE="$(uname -m)_$(uname -s)"
fi

ln -fs libft_malloc.so "libft_malloc_${HOSTTYPE}.so"