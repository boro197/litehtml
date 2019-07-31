#include <litehtml.h>
#include <JuceHeader.h>

using namespace litehtml;

class container_juce final : public document_container, public Component, public MouseListener{
public:
    container_juce(int a_DefaultFontSize);

    void setDocument(document::ptr a_Document);
    void paint (Graphics& g) override;
    void resized() override;
    void drawBorder(Graphics &hdc, border a_Border, int x, int y, int width, int height);
    void visibleAreaChanged (const Rectangle< int > &newVisibleArea);

    void mouseMove (const MouseEvent &event) override;
    void mouseEnter (const MouseEvent &event) override;
    void mouseExit (const MouseEvent &event) override;
    void mouseDown (const MouseEvent &event) override;
    void mouseUp (const MouseEvent &event) override;

    litehtml::uint_ptr create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;
    void delete_font(litehtml::uint_ptr hFont) override;
    int text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;
    void draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;
    int pt_to_px(int pt) override;
    int get_default_font_size() const override;
    const litehtml::tchar_t* get_default_font_name() const override;
    void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;
    void load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;
    void get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;
    void draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;
    void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;

    void set_caption(const litehtml::tchar_t* caption) override;
    void set_base_url(const litehtml::tchar_t* base_url) override;
    void link(const std::shared_ptr<litehtml::document>& doc, const litehtml::element::ptr& el) override;
    void on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override;
    void set_cursor(const litehtml::tchar_t* cursor) override;
    void transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;
    void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override;
    void set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;
    void del_clip() override;
    void get_client_rect(litehtml::position& client) const override;
    std::shared_ptr<litehtml::element> create_element(const litehtml::tchar_t *tag_name,
                                                      const litehtml::string_map &attributes,
                                                      const std::shared_ptr<litehtml::document> &doc) override;
    void get_media_features(litehtml::media_features& media) const override;
    void get_language(litehtml::tstring& language, litehtml::tstring & culture) const override;

private:
    document::ptr m_Document;
    litehtml::position::vector m_clips;

    String m_BaseUrl;
    int m_DefaultFontSize = 32;
    int m_VisibleX = 0;
    int m_VisibleY = 0;

    std::vector<int> m_NumberOfListElements;
    std::pair<int, int> m_ListIndex = {0, 1};

    const String m_LowerGreekAlphabet = CharPointer_UTF8("\u03B1\u03B2\u03B3\u03B4\u03B5\u03B6\u03B7\u03B8\u03B9\u03BA\u03BB\u03BC"
                                                         "\u03BD\u03BE\u03BF\u03C0\u03C1\u03C2\u03C3\u03C4\u03C5\u03C6\u03C7\u03C8\u03C9");
    const String m_UpperGreekAlphabet = CharPointer_UTF8("\u0391\u0392\u0393\u0394\u0395\u0396\u0397\u0398\u0399\u039A\u039B\u039C"
                                                         "\u039D\u039E\u039F\u03A0\u03A1\u03A2\u03A3\u03A4\u03A5\u03A6\u03A7\u03A8\u03A9");

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(container_juce)
};
