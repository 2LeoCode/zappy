#ifndef GFX_HXX
#define GFX_HXX

struct GfxContext {
  int argc;
  char const * const * argv;
};

int gfx_init(GfxContext * ctx);
int gfx_update(GfxContext * ctx);

#endif // !GFX_HXX
