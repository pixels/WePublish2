//
//  ReadViewACtrl.h
//  WePublish
//
//  Created by Yusuke Kikkawa on 10/06/27.
//  Copyright 2010 3di. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ReadViewBaseCtrl.h"

@interface ReadViewACtrl : ReadViewBaseCtrl {
	UIScrollView *_scrollView;
	UIScrollView *_scrollZoomView;
	UIImageView *_imageZoomView;
	BOOL _zooming;
	BOOL _zoomChangePage;
	BOOL _zoomNextPage;
}

@property (nonatomic, retain) IBOutlet UIScrollView *scrollView;
@property (nonatomic, retain) IBOutlet UIScrollView *scrollZoomView;
@property (nonatomic, retain) IBOutlet UIImageView *imageZoomView;
@property (nonatomic, assign) BOOL zooming;

- (void)scrollViewDidScroll:(UIScrollView *)sender;
- (void)setPage:(NSInteger)selectPage small:(BOOL)small;
- (void)releaseFarBooks:(NSInteger)targetPage;

@end
