static VALUE
format_<%=tp%>(VALUE fmt, dtype* x)
{
    // fix-me
    char s[48];
    int n;

    if (NIL_P(fmt)) {
        n = m_sprintf(s,*x);
        return rb_str_new(s,n);
    }
    return rb_funcall(fmt, '%', 1, m_data_to_num(*x));
}

static void
<%=c_iterator%>(na_loop_t *const lp)
{
    size_t  i;
    char   *p1, *p2;
    ssize_t s1, s2;
    size_t *idx1;
    dtype *x;
    VALUE y;
    VALUE fmt = lp->option;
    INIT_COUNTER(lp, i);
    INIT_PTR_IDX(lp, 0, p1, s1, idx1);
    INIT_PTR(lp, 1, p2, s2);
    if (idx1) {
        for (; i--;) {
            x = (dtype*)(p1 + *idx1);  idx1++;
            y = format_<%=tp%>(fmt, x);
            *(VALUE*)(p2) = y;
            p2 += s2;
        }
    } else {
        for (; i--;) {
            x = (dtype*)p1;  p1+=s1;
            y = format_<%=tp%>(fmt, x);
            *(VALUE*)(p2) = y;
            p2 += s2;
        }
    }
}

/*
  Format elements into strings.
  @overload <%=op_map%> format
  @param [String] format
  @return [NArray::RObject] array of formated strings.
*/
static VALUE
<%=c_instance_method%>(int argc, VALUE *argv, VALUE self)
{
    VALUE fmt=Qnil;

    ndfunc_arg_in_t ain[2] = {{Qnil,0},{sym_option}};
    ndfunc_arg_out_t aout[1] = {{cRObject,0}};
    // inplace not allowd
    ndfunc_t ndf = { <%=c_iterator%>, FULL_LOOP, 2, 1, ain, aout };

    rb_scan_args(argc, argv, "01", &fmt);
    return na_ndloop(&ndf, 2, self, fmt);
}
