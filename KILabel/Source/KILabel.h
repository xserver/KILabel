/***********************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Matthew Styles
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ***********************************************************************************/

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Constants for identifying link types we can detect
 */
typedef NS_ENUM(NSUInteger, KILinkType)
{
    KILinkTypeUserHandle,   //  "@"
    KILinkTypeHashtag,  //"#"
    KILinkTypeURL,      //URLs, http etc
    KILinkTypePhoneNumber,      //  Phone number
};

/**
 *  Flags for specifying combinations of link types as a bitmask
 */
typedef NS_OPTIONS(NSUInteger, KILinkTypeOption)
{
    KILinkTypeOptionNone = 0,   //  No links
    
    KILinkTypeOptionUserHandle = 1 << KILinkTypeUserHandle,
    KILinkTypeOptionHashtag = 1 << KILinkTypeHashtag,
    KILinkTypeOptionURL = 1 << KILinkTypeURL,
    KILinkTypeOptionPhoneNumber = 1 << KILinkTypePhoneNumber,
    
    KILinkTypeOptionAll = NSUIntegerMax,    //  all link types
};


@class KILabel;

/**
 *  Type for block that is called when a link is tapped
 *
 *  @param label  The KILabel in which the tap took place
 *  @param string Content of the link that was tapped, includes @ or # tokens
 *  @param range  The range of the string within the label's text
 */
typedef void (^KILinkTapHandler)(KILabel *label, NSString *string, NSRange range);

extern NSString * const KILabelLinkTypeKey;
extern NSString * const KILabelRangeKey;
extern NSString * const KILabelLinkKey;





/**
 * A UILabel subclass that highlights links, hashtags and usernames and enables response to user
 * interactions with those links.
 **/
IB_DESIGNABLE
@interface KILabel : UILabel <NSLayoutManagerDelegate>

/** ****************************************************************************************** **
 * @name Setting the link detector
 ** ****************************************************************************************** **/

/**
 * Enable/disable automatic detection of links, hashtags and usernames.
 */
@property (nonatomic, assign, getter = isAutomaticLinkDetectionEnabled) IBInspectable BOOL automaticLinkDetectionEnabled;

/**
 * Specifies the combination of link types to detect. Default value is KILinkTypeAll.
 */
@property (nonatomic, assign) IBInspectable KILinkTypeOption linkDetectionTypes;

/**
 * Set containing words to be ignored as links, hashtags or usernames.
 *
 * @discussion The comparison between the matches and the ignored words is case insensitive.
 */
@property (nullable, nonatomic, strong) NSSet *ignoredKeywords;



@property (nonatomic, copy) NSString *userHandlePattern;    //  default = nil, use system.



/** ****************************************************************************************** **
 * @name Format & Appearance
 ** ****************************************************************************************** **/

/**
 * The color used to highlight selected link background.
 *
 * @discussion The default value is (0.95, 0.95, 0.95, 1.0).
 */
@property (nullable, nonatomic, copy) IBInspectable UIColor *selectedLinkBackgroundColor;

/**
 * Flag sets if the sytem appearance for URLs should be used (underlined + blue color). Default value is NO.
 */
@property (nonatomic, assign) IBInspectable BOOL systemURLStyle;

#pragma mark - Attributes
/**
 * Get the current attributes for the given link type.
 *
 * @param linkType The link type to get the attributes.
 * @return A dictionary of text attributes.
 * @discussion Default attributes contain colored font using the tintColor color property.
 */
- (nullable NSDictionary*)attributesForLinkType:(KILinkType)linkType;

/**
 * Set the text attributes for each link type.
 *
 * @param attributes The text attributes.
 * @param linkType The link type.
 * @discussion Default attributes contain colored font using the tintColor color property.
 */
- (void)setAttributes:(nullable NSDictionary*)attributes forLinkType:(KILinkType)linkType;

/**
 *  判断是否点中 link（URL、@、#、Phone）
 *
 *  @param point 用户点击的point
 *
 *  @return 是否点中 KILinkTypeOption，点中则使用 KILinkTapHandler
 */
- (BOOL)handleTouchPoint:(CGPoint)point;

#pragma mark - Callback block for KILinkType link tap
@property (nullable, nonatomic, copy) KILinkTapHandler userHandleLinkTapHandler;
@property (nullable, nonatomic, copy) KILinkTapHandler hashtagLinkTapHandler;
@property (nullable, nonatomic, copy) KILinkTapHandler urlLinkTapHandler;
@property (nullable, nonatomic, copy) KILinkTapHandler phoneNumberTapHandler;


#pragma mark - Geometry

/**
 * Returns a dictionary of data about the link that it at the location. Returns nil if there is no link.
 *
 * A link dictionary contains the following keys:
 *
 * - **KILabelLinkTypeKey**, a TDLinkType that identifies the type of link.
 * - **KILabelRangeKey**, the range of the link within the label text.
 * - **KILabelLinkKey**, the link text. This could be an URL, handle or hashtag depending on the linkType value.
 *
 * @param point The point in the coordinates of the label view.
 * @return A dictionary containing the link.
 */
- (nullable NSDictionary*)linkAtPoint:(CGPoint)point;

@end

NS_ASSUME_NONNULL_END
