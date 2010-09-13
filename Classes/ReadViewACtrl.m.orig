    //
//  ReadViewACtrl.m
//  WePublish
//
//  Created by Yusuke Kikkawa on 10/06/27.
//  Copyright 2010 3di. All rights reserved.
//

#import "ReadViewACtrl.h"
#import "Util.h"
#import "Define.h"
#import "DirectionType.h"
#import "UIImageViewWithTouch.h"

#define USE_FLICK_PAGE_CHANGE NO
#define PAGE_CHANGE_FLICK_LENGTH 40

@implementation ReadViewACtrl
@synthesize scrollView = _scrollView;
@synthesize scrollZoomView = _scrollZoomView;
@synthesize imageZoomView = _imageZoomView;
@synthesize zooming = _zooming;

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)setup:(NSString *)uuid selectPage:(NSUInteger)selectPage pageNum:(NSInteger)pageNum direction:(NSInteger)direction {
	[super setup:uuid selectPage:selectPage pageNum:pageNum direction:direction];
	
	_scrollView.frame = CGRectMake(0, 0, WINDOW_AW, WINDOW_AH);
	_scrollView.contentSize = CGSizeMake(WINDOW_AW * pageNum, WINDOW_AH);
	
	NSInteger scrollPointX;
	if (_direction == DIRECTION_LEFT) {
		scrollPointX = _maxPage - selectPage;
	} else {
		scrollPointX = selectPage - 1;
	}
	
	_scrollView.contentOffset = CGPointMake(_scrollView.frame.size.width * scrollPointX, 0);
	[self setPage:selectPage small:NO];
}

- (BOOL)isNext {
	if (_currentPage < _maxPage)
		return YES;
	
	return NO;
}

- (void)next {
	[super next];
	
	NSInteger targetPage = 	_currentPage + 1;
	if (targetPage > _maxPage)
		return;
	
	NSInteger scrollPointX;
	if (_direction == DIRECTION_LEFT) {
		scrollPointX = _maxPage - targetPage;
	} else {
		scrollPointX = targetPage - 1;
	}
	
	_scrollView.contentOffset = CGPointMake(_scrollView.frame.size.width * scrollPointX, 0);
	[self releaseFarBooks:targetPage];
}

- (BOOL)isPrev {
	if (_currentPage > 1)
		return YES;
	
	return NO;
}

- (void)prev {
	[super prev];
	
	NSInteger targetPage = 	_currentPage - 1;
	if (targetPage < 1)
		return;
	
	NSInteger scrollPointX;
	if (_direction == DIRECTION_LEFT) {
		scrollPointX = _maxPage - targetPage;
	} else {
		scrollPointX = targetPage - 1;
	}

	_scrollView.contentOffset = CGPointMake(_scrollView.frame.size.width * scrollPointX, 0);
	[self releaseFarBooks:targetPage];
}

- (void)requestPage:(NSInteger)targetPage {
	[super requestPage:targetPage];
	
	NSInteger scrollPointX;
	if (_direction == DIRECTION_LEFT) {
		scrollPointX = _maxPage - targetPage;
	} else {
		scrollPointX = targetPage - 1;
	}
	
	_scrollView.contentOffset = CGPointMake(_scrollView.frame.size.width * scrollPointX, 0);
}

- (void)scrollViewDidScroll:(UIScrollView *)sender {
	if (sender == _scrollView) {
		CGFloat pageWidth = _scrollView.frame.size.width;  
		NSInteger targetPage = floor((_scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
		if (_direction == DIRECTION_LEFT)
			targetPage = _maxPage - targetPage;
		else {
			targetPage = targetPage + 1;
		}
		
		[self setPage:targetPage small:YES];
	}
	else if (sender == _scrollZoomView) {
		float zsw = _scrollZoomView.frame.size.width;
		float zox = _scrollZoomView.contentOffset.x;
		float zzs = _scrollZoomView.zoomScale;
		float pageChangeOffset = PAGE_CHANGE_FLICK_LENGTH * zzs;
		
		if (zox < -pageChangeOffset) {
			if (_direction == DIRECTION_LEFT) {
				_zoomNextPage = YES;
				_zoomChangePage = YES;
			}
			else {
				_zoomNextPage = NO;
				_zoomChangePage = YES;
			}
		}
		else if (zox > zsw * (zzs - 1) + pageChangeOffset) {
			if (_direction == DIRECTION_LEFT) {
				_zoomNextPage = NO;
				_zoomChangePage = YES;
			}
			else {
				_zoomNextPage = YES;
				_zoomChangePage = YES;
			}
		}
	}
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {

	if (scrollView == _scrollView) {
//		if (_scrollOffsetX > scrollView.contentOffset.x) {
//			if (_direction == DIRECTION_LEFT) {
//				NSLog(@"scrollViewDidEndScrollingAnimation Next");
//			} else {
//				NSLog(@"scrollViewDidEndScrollingAnimation Prev");
//			}
//		} else {
//			if (_direction == DIRECTION_LEFT) {
//				NSLog(@"scrollViewDidEndScrollingAnimation Prev");
//			} else {
//				NSLog(@"scrollViewDidEndScrollingAnimation Next");
//			}
//		}
		
		[self setPage:_currentPage small:NO];
		[self releaseFarBooks:_currentPage];
	}
	else if (scrollView == _scrollZoomView) {
//		NSLog(@"scrollViewDidEndDecelerating scrollZoomView.");
		
		if (_zoomChangePage) {
			if (USE_FLICK_PAGE_CHANGE) {
				[_scrollZoomView setZoomScale:1 animated:YES];
				[_scrollZoomView setHidden:YES];
				[_scrollView setScrollEnabled:YES];
				_zooming = NO;
				
				if (_zoomNextPage && [self isNext]) {
					[self next];
				}
				else if ([self isPrev]){
					[self prev];
				}
			}
			
			_zoomChangePage = NO;
		}
	}
}

- (void)releaseFarBooks:(NSInteger)targetPage {
	for (NSInteger i = 1; i < _maxPage; i++) {
		if (i < (targetPage - 2) || (targetPage + 2) < i) {
			NSNumber *number = [NSNumber numberWithInteger:i];
			if ([_booksList objectForKey:number]) {
				[super releaseBook:number removeFromList:YES];
			}
		}
	}
}

- (void)setPage:(NSInteger)selectPage small:(BOOL)small {
	
//	NSLog(@"page: %d", selectPage);
	
	if (selectPage != _currentPage)
		[super setPage:selectPage small:small];
	
	NSInteger readNum = small ? 3 : 3;
	NSInteger readOffset = small ? 1 : 1;
	NSInteger selectPageWithOffset;
	for (NSInteger i = 0; i < readNum; i++) {
		selectPageWithOffset = selectPage + (i - readOffset);
		NSInteger pagePosition = selectPageWithOffset;
		if (_direction == DIRECTION_LEFT)
			pagePosition = _maxPage - pagePosition;
		else {
			pagePosition = pagePosition - readOffset;
		}
		
		NSNumber *number = [NSNumber numberWithInteger:selectPageWithOffset];
		if ([_booksList objectForKey:number]) {
//			NSLog(@"already exist page: %d", selectPageWithOffset);
		} else {
			NSString *documentDir = [[NSString alloc] initWithFormat:@"%@/%@/%@", [Util getLocalDocument], BOOK_DIRECTORY, _uuid];
			NSString *image_path = [Util makeBookPathFormat:documentDir pageNo:selectPageWithOffset extension:BOOK_EXTENSION];
			UIImage *image = [[UIImage alloc] initWithContentsOfFile:image_path];
			if (image)
			{
				UIImageViewWithTouch *imageView = [[UIImageViewWithTouch alloc] initWithImage:image];
				[imageView setContentMode:UIViewContentModeScaleAspectFit];
				[imageView setUserInteractionEnabled:YES];
				[imageView setTag:selectPageWithOffset];
				[imageView setFrame:CGRectMake(WINDOW_AW * pagePosition, 0, WINDOW_AW, WINDOW_AH)];
				[_scrollView addSubview:imageView];
				[imageView release];
				[image release];
				[_booksList setObject:imageView forKey:number];
				
//				NSLog(@"add page: %d pagePosition: %d", selectPageWithOffset, pagePosition);
			}
			[image_path release];
			[documentDir release];
		}
		
		if (selectPage == selectPageWithOffset) {
			UIImageViewWithTouch *iv = (UIImageViewWithTouch *)[_booksList objectForKey:number];
			[_imageZoomView setImage:iv.image];
		}
	}
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView {  

	if (scrollView == _scrollView) {
		[_scrollZoomView setHidden:NO];
		[_scrollZoomView setZoomScale:_scrollZoomView.zoomScale + 0.05];
//		NSLog(@"viewForZoomingInScrollView _scrollView");
	}
	else if (scrollView == _scrollZoomView) {
//		NSLog(@"viewForZoomingInScrollView _scrollZoomView");
		if (!_zooming) {
			_zooming = YES;
			[_scrollView setScrollEnabled:NO];
		}
		
		return self.imageZoomView;
	}
	
	return nil;
}

- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale {
//	NSLog(@"scrollViewDidEndZooming");
	
	if (scrollView == _scrollZoomView) {
		if (_zooming) {
			if (_scrollZoomView.zoomScale <= 1) {
				_zooming = NO;
				[_scrollZoomView setHidden:YES];
				[_scrollView setScrollEnabled:YES];
			}
		}
	}
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	[self.imageZoomView release];
	[self.scrollZoomView release];
	[self.scrollView release];
    [super dealloc];
}

@end
