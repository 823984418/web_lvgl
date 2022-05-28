#include "webLvgl.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <sdl/sdl.h>
#include <indev/mouse.h>
#include <indev/mousewheel.h>
#include <indev/keyboard.h>

_lv_disp_t *disp1;
int monitor_hor_res;
int monitor_ver_res;

static void hal_init() {
    sdl_init();

    static lv_disp_draw_buf_t disp_buf1;
    auto *buf1_1 = static_cast<lv_color_t *>(malloc(sizeof(lv_color_t) * monitor_hor_res * monitor_ver_res));
    lv_disp_draw_buf_init(&disp_buf1, buf1_1, nullptr, monitor_hor_res * monitor_ver_res);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf1;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = monitor_hor_res;
    disp_drv.ver_res = monitor_ver_res;
    disp1 = lv_disp_drv_register(&disp_drv);

    lv_group_t *g = lv_group_create();
    lv_group_set_default(g);

    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb = sdl_mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);
    lv_indev_set_group(mouse_indev, g);

    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2);
    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = sdl_keyboard_read;
    lv_indev_t *kb_indev = lv_indev_drv_register(&indev_drv_2);
    lv_indev_set_group(kb_indev, g);

    static lv_indev_drv_t indev_drv_3;
    lv_indev_drv_init(&indev_drv_3);
    indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_3.read_cb = sdl_mousewheel_read;
    lv_indev_t *enc_indev = lv_indev_drv_register(&indev_drv_3);
    lv_indev_set_group(enc_indev, g);

}

void do_loop(void *arg) {
    lv_tick_inc(1000 / 144);
    lv_task_handler();

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        mouse_handler(&event);
        keyboard_handler(&event);
        mousewheel_handler(&event);
    }

}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        monitor_hor_res = atoi(argv[1]);
    } else {
        monitor_hor_res = 1920;
    }
    if (argc > 2) {
        monitor_ver_res = atoi(argv[2]);
    } else {
        monitor_ver_res = 1080;
    }
    lv_init();
    hal_init();


    emscripten_set_main_loop_arg(do_loop, nullptr, -1, true);
}

using namespace emscripten;

void base_event_handle(lv_event_t *event) {
    val *jsHandle = (val *) event->user_data;
    (*jsHandle).operator()(event);
}

EMSCRIPTEN_BINDINGS(WebLvgl) {

    enum_<lv_event_code_t>("event_code_t")
            .value("ALL", LV_EVENT_ALL);

    class_<lv_color_t>("color_t")
            .property("full", &lv_color_t::full)
            .property("alpha", optional_override([](const lv_color_t &o) {
                return o.ch.alpha;
            }), optional_override([](lv_color_t &o, uint8_t v) {
                o.ch.alpha = v;
            }))
            .property("red", optional_override([](const lv_color_t &o) {
                return o.ch.red;
            }), optional_override([](lv_color_t &o, uint8_t v) {
                o.ch.red = v;
            }))
            .property("green", optional_override([](const lv_color_t &o) {
                return o.ch.green;
            }), optional_override([](lv_color_t &o, uint8_t v) {
                o.ch.green = v;
            }))
            .property("blue", optional_override([](const lv_color_t &o) {
                return o.ch.blue;
            }), optional_override([](lv_color_t &o, uint8_t v) {
                o.ch.blue = v;
            }));

    class_<_lv_obj_t>("obj_t");
    class_<_lv_event_t>("event_t")
            .function("get_current_target", optional_override([](_lv_event_t *o) {
                return o->current_target;
            }), allow_raw_pointers())
            .function("set_current_target", optional_override([](_lv_event_t *o, _lv_obj_t *v) {
                o->current_target = v;
            }), allow_raw_pointers())
            .function("get_target", optional_override([](_lv_event_t *o) {
                return o->target;
            }), allow_raw_pointers())
            .function("set_target", optional_override([](_lv_event_t *o, _lv_obj_t *v) {
                o->target = v;
            }), allow_raw_pointers())
            .property("code", &_lv_event_t::code);

    function("init", lv_init);

    function("scr_act", lv_scr_act, allow_raw_pointers());

    function("obj_create", lv_obj_create, allow_raw_pointers());
    function("btn_create", lv_btn_create, allow_raw_pointers());
    function("label_create", lv_label_create, allow_raw_pointers());
    function("color_black", lv_color_black);
    function("obj_dpx", lv_obj_dpx, allow_raw_pointers());
    function("obj_set_style_bg_color", lv_obj_set_style_bg_color, allow_raw_pointers());
    function("obj_get_index", lv_obj_get_index, allow_raw_pointers());
    function("obj_get_child", lv_obj_get_child, allow_raw_pointers());

    function("obj_add_event_cb", optional_override([](lv_obj_t *obj, val event_cb, lv_event_code_t filter) {
        lv_obj_add_event_cb(obj, base_event_handle, filter, new val(event_cb));
    }), allow_raw_pointers());
    function("obj_set_size", lv_obj_set_size, allow_raw_pointers());
    function("obj_center", lv_obj_center, allow_raw_pointers());
    function("label_set_text", optional_override([](lv_obj_t *obj, const std::string &text) {
        const char *str = text.c_str();
        lv_label_set_text(obj, str);
    }), allow_raw_pointers());
    function("label_get_text", optional_override([](lv_obj_t *obj) {
        return std::string(lv_label_get_text(obj));
    }), allow_raw_pointers());

    function("version_major", lv_version_major);
    function("version_minor", lv_version_minor);
    function("version_patch", lv_version_patch);
    function("version_info", optional_override([]() {
        return std::string(lv_version_info());
    }));
}
