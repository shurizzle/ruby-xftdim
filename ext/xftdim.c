#include <ruby/ruby.h>
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

XftFont *load_font(char *, Display *);
void textdim(char *, int, char *, int *);
VALUE rb_cString_xftdim(VALUE, VALUE);

void Init_xftdim() {
    rb_define_method(rb_cString, "xftdim", rb_cString_xftdim, 1);
}

VALUE
rb_cString_xftdim(VALUE self, VALUE font) {
    int d[2];
    VALUE dims = rb_ary_new();
    if (rb_type(font) != T_STRING) {
        rb_raise(rb_eArgError, "Argument must be a string");
    }

    rb_funcall(self, rb_intern("encode!"), 1, rb_str_new2("UTF-8"));
    rb_funcall(font, rb_intern("encode!"), 1, rb_str_new2("UTF-8"));
    textdim(RSTRING_PTR(self), rb_funcall(self, rb_intern("length"), 0), RSTRING_PTR(font), d);
    rb_ary_push(dims, INT2FIX(d[0]));
    rb_ary_push(dims, INT2FIX(d[1]));

    return dims;
}

void
textdim(char * string, int len, char * font_name, int * dims) {
    XftFont *font;
    Display *dpy;
    XGlyphInfo extents;

    if (!(dpy = XOpenDisplay(NULL)))
        rb_raise(rb_eException, "Can't connect to X server %s\n", XDisplayName(NULL));

    font = load_font(font_name, dpy);
    XftTextExtentsUtf8(dpy, font, (const FcChar8 *) string, len, &extents);
    dims[0] = extents.width - extents.x;
    dims[1] = font->height;
    XCloseDisplay(dpy);
}

XftFont *
load_font(char * font_name, Display *dpy) {
    XftFont *font = NULL;

    if (!(font = XftFontOpenName(dpy, DefaultScreen(dpy), font_name)))
        rb_raise(rb_eException, "Can't locate '%s`\n", font_name);
    return font;
}
