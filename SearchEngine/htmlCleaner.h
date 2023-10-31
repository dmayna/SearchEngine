#pragma once

#include <string>

using namespace std;
/**
 * Cleans simple, validating HTML 4/5 into plain text.
 *
 * @author Dmayna
 */
class HtmlCleaner
{
private:
    /* data */
public:
    HtmlCleaner(/* args */);

    /**
	 * Removes all HTML tags and certain block elements from the provided text.
	 * The block elements removed include: head, style, script, noscript, iframe,
	 * and svg.
	 *
	 * @param html the HTML to strip tags and elements from
	 * @return text clean of any HTML tags and certain block elements
	 */
	string stripHtml(string html);

    /**
	 * Removes comments and certain block elements from the provided html. The block
	 * elements removed include: head, style, script, noscript, iframe, and svg.
	 *
	 * @param html the HTML to strip comments and block elements from
	 * @return text clean of any comments and certain HTML block elements
	 */
	string stripBlockElements(string html);

    /**
	 * Replaces all HTML entities with an empty string. For example,
	 * "2010&ndash;2012" will become "20102012".
	 *
	 * @param html text including HTML entities to remove
	 * @return text without any HTML entities
	 */
	string stripEntities(string html);

    /**
	 * Replaces all HTML tags with an empty string. For example, "A<b>B</b>C" will
	 * become "ABC".
	 *
	 * @param html text including HTML tags to remove
	 * @return text without any HTML tags
	 */
	string stripTags(string html);

    /**
	 * Replaces all HTML comments with a single space if the comment tags span
	 * multiple lines. Otherwise, replaces with an empty string. For example:
	 *
	 * <pre>
	 * A&lt;!-- B --&gt;C
	 * </pre>
	 *
	 * ...will become "AC" but this comment:
	 *
	 * <pre>
	 * A&lt;!--
	 * B --&gt;C
	 * </pre>
	 *
	 * ...will become"A C" instead because it spanned multiple lines. Note that this
	 * only considers newlines within the comment, not the surrounding HTML.
	 *
	 * @param html text including HTML comments to remove
	 * @return text without any HTML comments
	 *
	 */
	string stripComments(string html);

    /**
	 * Replaces everything between the element tags and the element tags
	 * themselves with a single space if the tags span multiple lines. Otherwise,
	 * replaces with an empty string. For example, consider the html code: *
	 *
	 * <pre>
	 * &lt;style type="text/css"&gt;body { font-size: 10pt; }&lt;/style&gt;
	 * </pre>
	 *
	 * If removing the "style" element, all of the above code will be removed, and
	 * replaced with an empty string. Note that this only considers newlines
	 * within the element tags, not the surrounding HTML.
	 *
	 * @param html text including HTML elements to remove
	 * @param name name of the HTML element (like "style" or "script")
	 * @return text without that HTML element
	 *
	 */
	string stripElement(string html, string name);

    /**
     * 
     * 
     * 
    */
   string stripCss(string html);

    /**
	 * Returns true if the provided input has one or more newlines.
	 * 
	 * @param input the input text to test against
	 * @return true if the input has one or more newlines
	 */
	bool hasNewline(string input);
};
