#include "container_juce.hpp"

#include <istream>
#include <iterator>
#include<string>

container_juce::container_juce(int a_DefaultFontSize) : document_container (), juce::Component(), juce::MouseListener(),
    m_DefaultFontSize(a_DefaultFontSize)
{
}

void container_juce::setDocument(document::ptr a_Document)
{
    m_Document = a_Document;
}

void container_juce::paint(Graphics &g)
{
    auto rectangle = getLocalBounds();

    m_Document->render(std::max(rectangle.getWidth(), 1));

    litehtml::position clip;
    clip.width 	= getWidth();
    clip.height = getHeight();
    clip.x 		= m_VisibleX;

    clip.y 		= m_VisibleY;

    m_Document->draw(static_cast<litehtml::uint_ptr>(&g), clip.x, clip.y, &clip);
}

void container_juce::resized()
{
    m_Document->media_changed();
}

void container_juce::drawBorder(Graphics &hdc, border a_Border, int x, int y, int width, int height)
{
    auto color = a_Border.color;
    hdc.setColour(Colour::fromRGBA(color.red, color.green, color.blue, color.alpha));
    hdc.drawLine(x, y, x + width, y + height, a_Border.width);
}

void container_juce::mouseMove(const MouseEvent &event)
{
    litehtml::position::vector vec;
    auto position = event.getPosition();
    if (m_Document->on_mouse_over(position.getX(), position.getY(), position.getX(), position.getY(), vec))
    {
        repaint();
    }
    m_Document->media_changed();
}

void container_juce::mouseEnter(const MouseEvent &event)
{
    litehtml::position::vector vec;
    auto position = event.getPosition();
    if (m_Document->on_mouse_over(position.getX(), position.getY(), position.getX(), position.getY(), vec)){
        repaint();
    }
}

void container_juce::mouseExit(const MouseEvent &event)
{
    (void) event;
    litehtml::position::vector vec;
    if (m_Document->on_mouse_leave(vec))
        repaint();
}

void container_juce::mouseDown(const MouseEvent &event)
{
    litehtml::position::vector vec;
    if (m_Document->on_lbutton_down(event.getMouseDownX(), event.getMouseDownY(),event.getMouseDownX(), event.getMouseDownY(), vec)){
        repaint();
    }
    m_Document->media_changed();
}

void container_juce::mouseUp(const MouseEvent &event)
{
    litehtml::position::vector vec;
    if (m_Document->on_lbutton_up(event.getMouseDownX(), event.getMouseDownY(),event.getMouseDownX(), event.getMouseDownY(), vec))
        repaint();
    m_Document->media_changed();
}

litehtml::uint_ptr container_juce::create_font(const litehtml::tchar_t *faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics *fm)
{
    Font *font = new Font(faceName, size, Font::plain);

    font->setBold(weight > 100);
    font->setItalic(italic == litehtml::fontStyleItalic);
    font->setUnderline(decoration & litehtml::font_decoration_underline);
    font->setHeight(size);

    fm->height = size;

    return std::move(font);
}

void container_juce::delete_font(uint_ptr hFont)
{
    auto font = (Font *) hFont;
    if(font) delete font;
}

int container_juce::text_width(const tchar_t *text, uint_ptr hFont)
{
    TextEditor textEditor(text);
    auto font = (Font *) hFont;
    if(!font) font = new Font(*get_default_font_name(), get_default_font_size());
    textEditor.setFont(*font);
    textEditor.setText(text);
    return textEditor.getTextWidth();
}

void container_juce::draw_text(uint_ptr hdc, const tchar_t *text, uint_ptr hFont, web_color color, const position &pos)
{
    auto graphics = (Graphics*)(hdc);
    Colour textColor = Colour::fromRGBA(color.red, color.green, color.blue, color.alpha);
    graphics->setColour(textColor);
    auto font = (Font *) hFont;
    graphics->setFont(std::move(*font));
    graphics->drawText(text, pos.x, pos.y, text_width(text, hFont), pos.height, Justification::left);
}

int container_juce::pt_to_px(int pt)
{
    return 0;
}

int container_juce::get_default_font_size() const
{
    return m_DefaultFontSize;
}

const tchar_t *container_juce::get_default_font_name() const
{
    return Font::getDefaultSerifFontName().toRawUTF8();
}

void container_juce::draw_list_marker(uint_ptr hdc, const list_marker &marker)
{
    auto graphics = (Graphics*) hdc;
    auto color = marker.color;
    auto pos = marker.pos;
    pos.y += pos.height * 4;
    graphics->setColour(Colour::fromRGBA(color.red, color.green, color.blue, color.alpha));

    String text = "";

    switch (marker.marker_type) {
    case list_style_type_none: {
        [[clang::fallthrough]];
    }
    case list_style_type_circle: {
        graphics->drawEllipse(pos.x, pos.y, pos.width / 2, pos.height / 2, 1);
        break;
    }
    case list_style_type_disc: {
        graphics->drawEllipse(pos.x, pos.y, pos.width / 2, pos.height / 2, pos.height / 2);
        break;
    }
    case list_style_type_square: {
        graphics->drawRect(pos.x, pos.y, pos.width / 2, pos.height / 2, pos.height / 2);
        break;
    }
    case list_style_type_armenian: {
        break;
    }
    case list_style_type_cjk_ideographic: {
        break;
    }
    case list_style_type_decimal_leading_zero: {
        if(m_ListIndex.second < 10) text = "0";
        [[clang::fallthrough]];
    }
    case list_style_type_decimal: {
        text += String::formatted("%c", '0' + m_ListIndex.second);
        break;
    }
    case list_style_type_georgian: {
        break;
    }
    case list_style_type_hebrew: {
        break;
    }
    case list_style_type_hiragana: {
        break;
    }
    case list_style_type_hiragana_iroha: {
        break;
    }
    case list_style_type_katakana: {
        break;
    }
    case list_style_type_katakana_iroha: {
        break;
    }
    case list_style_type_lower_alpha: {
        [[clang::fallthrough]];
    }
    case list_style_type_lower_greek: {
        text = String::formatted("%lc", m_LowerGreekAlphabet[m_ListIndex.second - 1]);
        break;
    }
    case list_style_type_lower_latin: {
        [[clang::fallthrough]];
    }
    case list_style_type_lower_roman: {
        text = String::formatted("%c", 'a' + m_ListIndex.second - 1);
        break;
    }
    case list_style_type_upper_alpha: {
        [[clang::fallthrough]];
    }
    case list_style_type_upper_latin: {
        [[clang::fallthrough]];
    }
    case list_style_type_upper_roman: {
        text = String::formatted("%c", 'A' + m_ListIndex.second - 1);
        break;
    }
    }

    Logger::writeToLog(String(text));

    if(!text.isEmpty()){
        String marker = text + ".";
        graphics->drawText(marker, pos.x, pos.y - get_default_font_size() / 2, text_width(marker.toRawUTF8(), nullptr), get_default_font_size(), Justification::left);
    }
    m_ListIndex.second++;
    if(m_ListIndex.second > m_NumberOfListElements[m_ListIndex.first]){
        m_ListIndex.second = 1;
        m_ListIndex.first == m_NumberOfListElements.size() - 1 ? m_ListIndex.first = 1 : m_ListIndex.first++;
    }
}

void container_juce::load_image(const tchar_t *src, const tchar_t *baseurl, bool redraw_on_ready)
{
    //TODO
}

void container_juce::get_image_size(const tchar_t *src, const tchar_t *baseurl, size &sz)
{
    String imageUrl = String(baseurl) + String(src);
    File file(imageUrl);
    auto image = ImageFileFormat::loadFrom(file);

    sz.width = image.getWidth();
    sz.height = image.getHeight();
}

void container_juce::draw_background(uint_ptr hdc, const background_paint &bg)
{
    auto graphics = (Graphics *) hdc;
    auto color = bg.color;
    URL url(bg.image);
    File file("./back.png");
    if(!file.exists()){
        auto task = url.downloadToFile(file);
        while(!task->isFinished());
    }
    Image image(Image::ARGB, getHeight(), getWidth(), false);
    image = ImageFileFormat::loadFrom(file);
    graphics->fillAll(Colour::fromRGBA(color.red, color.green, color.blue, color.alpha));
    if(image.isValid()) graphics->drawImage(image, getLocalBounds().toFloat());
    Logger::writeToLog("drawing bak");

}

void container_juce::draw_borders(uint_ptr hdc, const borders &borders, const position &draw_pos, bool root)
{
    return;
    auto graphics = (Graphics *) hdc;
    graphics->drawRect(getLocalBounds().toFloat(), borders.top.width);

    drawBorder(*graphics, borders.top, draw_pos.left(), draw_pos.top(), draw_pos.width, draw_pos.height);
    drawBorder(*graphics, borders.left, draw_pos.left(), draw_pos.top(), draw_pos.width, draw_pos.height);
    drawBorder(*graphics, borders.right, draw_pos.right(), draw_pos.top(), draw_pos.width, draw_pos.height);
    drawBorder(*graphics, borders.bottom, draw_pos.left(), draw_pos.top(), draw_pos.width, draw_pos.height);
    Logger::writeToLog("drawing borders");
    //TODO
}

void container_juce::set_caption(const tchar_t *caption)
{
    Logger::writeToLog(String::formatted("Setting caption %s", caption));
    setName(caption);
}

void container_juce::set_base_url(const tchar_t *base_url)
{
    m_BaseUrl = String(base_url);
}

void container_juce::link(const std::shared_ptr<document> &doc, const element::ptr &el)
{
    (void)doc;
    (void)el;
}

void container_juce::on_anchor_click(const tchar_t *url, const element::ptr &el)
{
    (void)el;

    URL anchor(url);
    if(!anchor.launchInDefaultBrowser()) Logger::writeToLog("Cannot open link");
}

void container_juce::set_cursor(const tchar_t *cursor)
{
    std::string mouseCursor = cursor;

    if (strcmp(cursor, "auto") == 0) setMouseCursor(MouseCursor::NormalCursor);
    else if (strcmp(cursor, "pointer") == 0) setMouseCursor(MouseCursor::PointingHandCursor);
    else if (strcmp(cursor, "crosshair") == 0) setMouseCursor(MouseCursor::CrosshairCursor);
    else setMouseCursor(MouseCursor::NormalCursor);
}

void container_juce::transform_text(tstring &text, text_transform tt)
{
    switch(tt)
    {
    case litehtml::text_transform::text_transform_none: return;
    case litehtml::text_transform::text_transform_lowercase: text = String(text).toLowerCase().toRawUTF8(); break;
    case litehtml::text_transform::text_transform_uppercase: text = String(text).toUpperCase().toRawUTF8(); break;
    case litehtml::text_transform::text_transform_capitalize: text[0] = String(text).toUpperCase().toRawUTF8()[0]; break;
    }
}

void container_juce::import_css(tstring &text, const tstring &url, tstring &baseurl)
{
    auto location = baseurl + url;
    File cssFile (location);
    if(!cssFile.exists()){
        printf("Css file %s does not exists", location.c_str());
        return;
    }
    else {
        auto contentOfFile = cssFile.loadFileAsString();
        text = contentOfFile.toRawUTF8();
    }
}

void container_juce::set_clip(const position &pos, const border_radiuses &bdr_radius, bool valid_x, bool valid_y)
{
    auto rectangle = getLocalBounds();
    litehtml::position clip_pos = pos;

    if(!valid_x)
    {
        clip_pos.x		= 0;
        clip_pos.width	= rectangle.getWidth();
    }

    if(!valid_y)
    {
        clip_pos.y		= 0;
        clip_pos.height	= rectangle.getHeight();
    }

    m_clips.push_back( clip_pos );
    //TODO

}

void container_juce::del_clip()
{
    if(!m_clips.empty()) m_clips.pop_back();
}

void container_juce::get_client_rect(position &client) const
{
    auto rectangle = getLocalBounds();

    client.move_to(rectangle.getX(), rectangle.getY());
    client.width = rectangle.getWidth();
    client.height = rectangle.getHeight();
}

std::shared_ptr<element> container_juce::create_element(const tchar_t *tag_name, const string_map &attributes, const std::shared_ptr<document> &doc)
{
    if(!strcmp(tag_name, "ul")) {
        if(m_NumberOfListElements.empty() || m_NumberOfListElements.back() != 0) {
            m_NumberOfListElements.push_back(0);
        }
    }
    else if(!strcmp(tag_name, "li")) m_NumberOfListElements.back()++;
    return std::shared_ptr<litehtml::element>();
}

void container_juce::get_media_features(media_features &media) const
{
    Rectangle<int> display = Desktop::getInstance().getDisplays().getMainDisplay().userArea;

    litehtml::position client;
    get_client_rect(client);

    media.type			= litehtml::media_type_screen;

    media.color			= 8;
    media.monochrome	= 0;
    media.color_index	= 256;
    media.resolution	= 96;

    media.width			= client.width;
    media.height		= client.height;
    media.device_width	= display.getWidth();
    media.device_height	= display.getHeight();
}

void container_juce::get_language(tstring &language, tstring &culture) const
{
    language = _t("en");
    culture = _t("");
}
