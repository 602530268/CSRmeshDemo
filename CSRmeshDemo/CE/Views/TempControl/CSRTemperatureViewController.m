//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

// This view is hardwired to display the internal air temperature and to allow the desired temperature to be set.
//
// Sensor Types
//  internal_air_temperature =  1,
//  desired_air_temperature  =  3
//

#import "CSRTemperatureViewController.h"
#import "CSRDevicesManager.h"
#import "CSRUtilities.h"
#import "CSRDatabaseManager.h"
#import "CSRConstants.h"

@implementation CSRTemperatureViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    if (!_selectedArea.desiredTemperatureSetByUser)
        _selectedArea.desiredTemperatureSetByUser = @20.0;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refreshView) name:SENSOR_VALUE_CHANGED object:nil];
}



- (void)viewDidDisappear:(BOOL)animated {
    // Disable continuous scan
    [[MeshServiceApi sharedInstance] setContinuousLeScanEnabled:NO];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


//============================================================================
-(void) viewDidAppear:(BOOL)animated {
    
    // Enable continuous scan
    [[MeshServiceApi sharedInstance] setContinuousLeScanEnabled:YES];
    
    _selectedDevice = [[CSRDevicesManager sharedInstance] selectedDevice];
    _selectedArea = [[CSRDevicesManager sharedInstance] selectedArea];
    
    
    if (_selectedArea) {
        NSString *title = [_selectedArea areaName];
        self.title = title;
    }
    else if (_selectedDevice) {
        NSString *title = [_selectedDevice name];
        self.title = title;
    }
    else
        self.title = @"CSRmesh";
    
    // Hide the navigation bar
//    [self.navigationController setNavigationBarHidden:YES];
    
    [self refreshView];
}

//============================================================================
// Add observers for selected area so that view components are automatically refreshed when the underlying property changes
-(void) createObserversForSelectedGroup
{
    // create observer for actual temperature, refresh view if it changes
    if (_selectedArea) {
        [_selectedArea.currentTemperature addObserver:self forKeyPath:@"currentTemperature" options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:NULL];
        
        [_selectedArea.desiredTemperatureAcknowledged addObserver:self forKeyPath:@"desiredTemperatureAcknowledged" options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:NULL];
    }
}

//============================================================================
// Remove observers
-(void) removeObserversForSelectedGroup
{
    [_selectedArea.currentTemperature removeObserver:self forKeyPath:@"currentTemperature"];
    [_selectedArea.desiredTemperatureAcknowledged removeObserver:self forKeyPath:@"desiredTemperatureAcknowledged"];
}

//============================================================================
// Update View
// Display actual temperature, if available
// Display desired temperature, set to 20 degrees initially, display in orange while unconfirmed
-(void)  refreshView
{
    UIColor *textColor = [UIColor lightGrayColor];
    if (_selectedArea) {
        NSString *actualTemp;
        if (_selectedArea.currentTemperature) {
            float temp = [_selectedArea.currentTemperature floatValue];
            actualTemp = [NSString stringWithFormat:@"%0.1f",temp];
        }
        else
            actualTemp = @"--.-";
        _actualTemperatureLabel.text = actualTemp;
        
        NSString *desiredTemp;
        if (_selectedArea.desiredTemperatureSetByUser) {
            float temp = [_selectedArea.desiredTemperatureSetByUser floatValue];
            desiredTemp = [NSString stringWithFormat:@"%0.1f",temp];
        }
        else
            desiredTemp = @"--.-";
        _desiredTemperatureLabel.text = desiredTemp;
        
        if (_selectedArea.desiredTemperatureSetByUser) {
            if (!_selectedArea.desiredTemperatureAcknowledged ||
                ![_selectedArea.desiredTemperatureSetByUser isEqualToNumber:_selectedArea.desiredTemperatureAcknowledged]) {
                textColor = [UIColor BACKGROUND_HIGHLIGHT];
            }
        }
    }
    else {
        _actualTemperatureLabel.text = @"--.-";
        _desiredTemperatureLabel.text = @"--.-";
    }
    
    _desiredTemperatureText.textColor = textColor;
}



//============================================================================
// KVO observer for groups->current temperature
-(void) observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    
    if ([keyPath isEqualToString:@"currentTemperature"]) {
        [self refreshView];
    }
    else if ([keyPath isEqualToString:@"isDesiredTemperatureAcknowledged"]) {
        _desiredTemperatureLabel.backgroundColor = [UIColor whiteColor];
        _desiredTemperatureLabel.textColor = [UIColor blackColor];
    }
}

//============================================================================
// Set the desired temperature for the area and call a mesh command
-(void) setDesiredTemperatureForCurrentArea :(float) desiredTemperature
{
    if (_selectedArea) {
        NSNumber *temperature = @(desiredTemperature);
        if (![_selectedArea.desiredTemperatureSetByUser isEqualToNumber:temperature]) {
            _selectedArea.desiredTemperatureSetByUser = temperature;
            [[CSRDevicesManager sharedInstance] setDesiredTemperatureForArea:_selectedArea];
        }
    }
    [self refreshView];
}


//============================================================================
// Increment the temperature by 0.5 for this group, ceiling is 30.0
- (IBAction)increaseTemperature:(id)sender
{
    float temperature = 20.0;
    if (_selectedArea) {
        if (_selectedArea.desiredTemperatureSetByUser) {
            temperature = [_selectedArea.desiredTemperatureSetByUser floatValue];
            if (temperature < 30.0) {
                temperature += 0.5;
                if (temperature > 30.0)
                    temperature = 30.0;
            }
            else
                return;
        }
        [self setDesiredTemperatureForCurrentArea:temperature];
    }
}

//============================================================================
// Decrement the temperature by 0.5 for this group, floor is 5.0
- (IBAction)decreaseTemperature:(id)sender
{
    float temperature = 20.0;
    if (_selectedArea) {
        if (_selectedArea.desiredTemperatureSetByUser) {
            temperature = [_selectedArea.desiredTemperatureSetByUser floatValue];
            if (temperature > 5.0) {
                temperature -= 0.5;
                if (temperature < 5.0)
                    temperature = 5.0;
            }
            else
                return;
        }
        [self setDesiredTemperatureForCurrentArea:temperature];
    }
}



@end
