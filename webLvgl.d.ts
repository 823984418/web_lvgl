declare function WebLvgl<T>(target?: T): Promise<T & typeof WebLvgl>;

declare module WebLvgl {
    const HEAP8: Int8Array;
    const HEAP16: Int16Array;
    const HEAP32: Int32Array;
    const HEAPF32: Float32Array;
    const HEAPF64: Float64Array;
    const HEAPU8: Uint8Array;
    const HEAPU16: Uint16Array;
    const HEAPU32: Uint32Array;

    enum event_code_t {
        ALL,
        PRESSED,
        PRESSING,
        PRESS_LOST,
        SHORT_CLICKED,
        LONG_PRESSED,
        LONG_PRESSED_REPEAT,
        CLICKED,
        RELEASED,
        SCROLL_BEGIN,
        SCROLL_END,
        SCROLL,
        GESTURE,
        KEY,
        FOCUSED,
        DEFOCUSED,
        LEAVE,
        HIT_TEST,
        COVER_CHECK,
        REFR_EXT_DRAW_SIZE,
        DRAW_MAIN_BEGIN,
        DRAW_MAIN,
        DRAW_MAIN_END,
        DRAW_POST_BEGIN,
        DRAW_POST,
        DRAW_POST_END,
        DRAW_PART_BEGIN,
        DRAW_PART_END,
        VALUE_CHANGED,
        INSERT,
        REFRESH,
        READY,
        CANCEL,
        DELETE,
        CHILD_CHANGED,
        CHILD_CREATED,
        CHILD_DELETED,
        SCREEN_UNLOAD_START,
        SCREEN_LOAD_START,
        SCREEN_LOADED,
        SCREEN_UNLOADED,
        SIZE_CHANGED,
        STYLE_CHANGED,
        LAYOUT_CHANGED,
        GET_SELF_SIZE,
        PREPROCESS
    }

    class color_t {
        full: number;
        alpha: number;
        red: number;
        green: number;
        blue: number;
    }

    class event_t {
        current_target: obj_t;
        target: obj_t;
        code: event_code_t;
    }

    class obj_t {
    }

    function scr_act(): obj_t;

    function obj_create(parent: obj_t): obj_t;

    function btn_create(parent: obj_t): obj_t;

    function label_create(parent: obj_t): obj_t;

    function textarea_create(parent: obj_t): obj_t;

    function keyboard_create(parent: obj_t): obj_t;

    function keyboard_set_textarea(kb: obj_t, ta: obj_t);

    function color_black(): color_t;

    function obj_dpx(obj: obj_t, n: number): color_t;

    function obj_set_style_bg_color(obj: obj_t, value: color_t, selector: number);

    function obj_get_index(obj: obj_t): number;

    function obj_get_child(obj: obj_t, id: number): obj_t;

    function obj_del(obj: obj_t);

    function obj_del_async(obj: obj_t);

    function obj_clean(obj: obj_t);

    function obj_add_event_cb(obj: obj_t, event_cb: (event: event_t) => void, filter: event_code_t);

    function obj_set_size(obj: obj_t, w: number, h: number);

    function obj_center(obj: obj_t);

    function label_set_text(obj: obj_t, text: string);

    function label_get_text(obj: obj_t): string;

    function version_major(): number;

    function version_minor(): number;

    function version_patch(): number;

    function version_info(): string;

}

