//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRNewEventShortcutViewController.h"
#import "CSRDatabaseManager.h"
#import "CSRmeshDevice.h"

//Cells for the tableView
#import "CSREventNameTextFieldCell.h"
#import "CSREventOnOffCell.h"
#import "CSREventConfigurationCell.h"
#import "CSREventTimeCell.h"
#import "CSREventRepeatCell.h"
#import "CSREventDevicesCell.h"

#import "CSREventTimeSelectorVC.h"
#import "CSREventControlVC.h"

//To find the source of the Segue
#import "CSREventsTableViewController.h"
#import "CSREventsDetailsViewController.h"

//App State Manager
#import "CSRAppStateManager.h"
#import "CSRDevicesManager.h"

//Entities
#import "CSRDeviceEntity.h"
#import "CSRAreaEntity.h"
#import "CSRUtilities.h"
#import "CSREventsManager.h"
#import "CSRDeviceEventsEntity.h"

#define kDatePickerTag              99     // view tag identifiying the date picker view

#define kDateKey        @"date"    // key for obtaining the data source item's date value

static NSString *kDatePickerID = @"datePicker"; // the cell containing the date picker
static NSString *kCSREventTimeCellIdentifier = @"eventTimeCellIdentifier";

static NSString *kCSREventConfigurationCell = @"eventConfigurationCellIdentifier";


#pragma mark -

@interface CSRNewEventShortcutViewController ()

@property (nonatomic, strong) NSArray *dataArray;

@property (weak, nonatomic) IBOutlet UIDatePicker *datePicker;
@property (nonatomic, strong) NSDateFormatter *dateFormatter;

@property (nonatomic, strong) NSIndexPath *datePickerIndexPath;
@property (assign) NSInteger pickerCellRowHeight;

//Event Name String
@property (nonatomic, strong) NSString *eventNameString;
//@property (nonatomic, strong) NSString *dateString;


@property (assign) BOOL onOffBool;
@property (assign) BOOL repeatBool;

//@property (nonatomic, retain) CSREventEntity *eventEntity;
@property (nonatomic, strong) NSArray *allDevicesArray;

@property (nonatomic, strong) NSNumber *hourField;
@property (nonatomic, strong) NSData *weekDaysData;

@property (nonatomic, retain) NSMutableArray *selectedDevicesArray;

@property (nonatomic, strong) CSREventsManager *eventsManager;
@property (nonatomic, strong) CSRAreaEntity *areaEntity;

@property (nonatomic, strong) UIColor *eventColor;
@property (nonatomic) CGFloat intensityFloat;
@property (nonatomic, assign) BOOL eventOnOff;
@property (nonatomic, assign) float eventTemperature;

@property (nonatomic, strong) NSString *timeString;
@property (nonatomic, assign) BOOL repeatOnOff;
@end


@implementation CSRNewEventShortcutViewController


- (void) viewDidAppear:(BOOL)animated {
    
    [super viewDidAppear:animated];
}

- (void) viewDidLoad {
    
    [super viewDidLoad];
    
    // setup our data source
    NSMutableArray *_allDeviceEventsArray = [NSMutableArray new];
    CSRDeviceEventsEntity *actionEntity = nil;
    
    NSSet *eventActions = _eventEntity.deviceEvents;
    for (CSRDeviceEventsEntity *deviceEvents in eventActions) {
        [_allDeviceEventsArray addObject:deviceEvents];
    }
    
    if (_allDeviceEventsArray) {
        actionEntity = [_allDeviceEventsArray objectAtIndex:0];
    }
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateStyle:NSDateFormatterMediumStyle];
    [dateFormatter setDateFormat:@"EEE,dd MMM yyyy"];
    
    NSDate *eventDate = [NSDate dateWithTimeIntervalSince1970:([actionEntity.eventTime doubleValue]/1000)];
    NSMutableDictionary *itemTwo = [@{kDateKey : [dateFormatter stringFromDate:eventDate] } mutableCopy];
    self.dataArray = @[itemTwo];
    
    [dateFormatter setDateFormat:@"HH:MM"];
    _timeString = [dateFormatter stringFromDate:eventDate];
    
    if (actionEntity.eventRepeatMills) {
        _repeatOnOff = YES;
    } else {
        _repeatOnOff = NO;
    }
    
    
    self.dateFormatter = [[NSDateFormatter alloc] init];
    [self.dateFormatter setDateStyle:NSDateFormatterMediumStyle];    // show medium-style date format
    [self.dateFormatter setDateFormat:@"EEE,dd MMM yyyy HH:MM"];
    
    _allDevicesArray = [NSArray new];
    _allDevicesArray = [[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects];
    
    //Date Picker View
    _datePicker.datePickerMode = UIDatePickerModeDateAndTime;
    
    // obtain the picker view cell's height, works because the cell was pre-defined in our storyboard
    UITableViewCell *pickerViewCellToCheck = [_eventCreationTableView dequeueReusableCellWithIdentifier:kDatePickerID];
    self.pickerCellRowHeight = CGRectGetHeight(pickerViewCellToCheck.frame);
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadTableViewWithColor:) name:@"colorTapped" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadTableViewWithIntensity:) name:@"sliderTapped" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadTableViewWithOnOff:) name:@"eventActivation" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadTableViewWithTemperature:) name:@"temperatureIncreased" object:nil];
    _selectedDevicesArray = [NSMutableArray new];
}


- (void) viewWillDisappear:(BOOL)animated {
    
    [super viewWillDisappear:animated];
//    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"colorTapped" object:nil];
//    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"sliderTapped" object:nil];
}

- (void) reloadTableViewWithColor:(NSNotification*)notification {
    
    _eventColor = (UIColor*)notification.userInfo[@"color"];
    [_eventCreationTableView reloadData];
}

- (void) reloadTableViewWithIntensity:(NSNotification*)notification {

    _intensityFloat = [notification.userInfo[@"intensity"] floatValue];
    [_eventCreationTableView reloadData];
}

- (void) reloadTableViewWithOnOff:(NSNotification*)notification {
    
    _eventOnOff = [notification.userInfo[@"eventStatus"] boolValue];
    [_eventCreationTableView reloadData];
}

- (void) reloadTableViewWithTemperature:(NSNotification*)notification {
    
    _eventTemperature = [notification.userInfo[@"temperature"] floatValue];
    [_eventCreationTableView reloadData];
}


- (BOOL)hasPickerForIndexPath:(NSIndexPath *)indexPath
{
    BOOL hasDatePicker = NO;
    
    NSInteger targetedRow = indexPath.row;
    targetedRow++;
    
    UITableViewCell *checkDatePickerCell = [_eventCreationTableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:targetedRow inSection:2]];
    UIDatePicker *checkDatePicker = (UIDatePicker *)[checkDatePickerCell viewWithTag:kDatePickerTag];
    
    hasDatePicker = (checkDatePicker != nil);
    return hasDatePicker;
}

- (void)updateDatePicker
{
    if (self.datePickerIndexPath != nil)
    {
        UITableViewCell *associatedDatePickerCell = [_eventCreationTableView cellForRowAtIndexPath:self.datePickerIndexPath];
        
        UIDatePicker *targetedDatePicker = (UIDatePicker *)[associatedDatePickerCell viewWithTag:kDatePickerTag];
        if (targetedDatePicker != nil)
        {
            // we found a UIDatePicker in this cell, so update it's date value
            //
            NSDictionary *itemData = self.dataArray[self.datePickerIndexPath.row - 2];
            [targetedDatePicker setDate:[itemData valueForKey:kDateKey] animated:NO];
        }
    }
}

- (BOOL)hasInlineDatePicker
{
    return (self.datePickerIndexPath != nil);
}

- (BOOL)indexPathHasPicker:(NSIndexPath *)indexPath
{
    return ([self hasInlineDatePicker] && self.datePickerIndexPath.row == indexPath.row);
}

- (BOOL)indexPathHasDate:(NSIndexPath *)indexPath
{
    BOOL hasDate = NO;
    
    if ((indexPath.row == 1) || [self hasInlineDatePicker])
    {
        hasDate = YES;
    }
    
    return hasDate;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    
    return 5;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    if (section == 0) {
        return 1;
    } else if (section == 1) {
        return 1;
    } else if (section == 2) {
        if ([self hasInlineDatePicker]) {
            return 3;
        }
        return 2;
    } else if (section == 3) {
        return 1;
    } else if (section == 4) {
        return [_allDevicesArray count];
    }
   return 0;
    
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    
    if (section == 2) {
        return LOCALIZEDSTRING(@"Configuration");
    } else if (section == 4) {
        return LOCALIZEDSTRING(@"Devices");
    }
    return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    if(section == 0) {
        return 2.;
    } else if (section == 1) {
        return 2.;
    } else if (section == 3) {
        return 2.;
    }
    return UITableViewAutomaticDimension;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (indexPath.section == 0) {
        return 44.;
    } else if (indexPath.section == 1) {
        return 60.;
    } else if (indexPath.section == 2) {
        return ([self indexPathHasPicker:indexPath] ? self.pickerCellRowHeight : _eventCreationTableView.rowHeight);
    } else if (indexPath.section == 3) {
        return 44.;
    } else if (indexPath.section == 4) {
        return 44.;
    }
    return 0;
}


- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Remove seperator inset
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsZero];
    }
    
    // Prevent the cell from inheriting the Table View's margin settings
    if ([cell respondsToSelector:@selector(setPreservesSuperviewLayoutMargins:)]) {
        [cell setPreservesSuperviewLayoutMargins:NO];
    }
    
    // Explictly set your cell's layout margins
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell *Cell = nil;
    
    if (indexPath.section == 0) {
        //eventNameTextFieldCellIdentifier
        CSREventNameTextFieldCell *Cell = [tableView dequeueReusableCellWithIdentifier:CSREventNameTextFieldCellIdentifier];
        if (!Cell) {
            Cell = [[CSREventNameTextFieldCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CSREventNameTextFieldCellIdentifier];
        }
        Cell.eventNameTextField.delegate = self;
        if (_eventEntity) {
            Cell.eventNameTextField.placeholder = _eventEntity.eventName;
        }
        
        return Cell;
        
    } else if (indexPath.section == 1) {
        //eventOnOffCellIdentifier
        CSREventOnOffCell *Cell = [tableView dequeueReusableCellWithIdentifier:CSREventOnOffCellIdentifier];
        if (!Cell) {
            Cell = [[CSREventOnOffCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CSREventOnOffCellIdentifier];
        }
        Cell.eventNameLabel.text = LOCALIZEDSTRING(@"Event on");
        Cell.eventDescriptionLabel.text = LOCALIZEDSTRING(@"Tap to deactivate the event");
        Cell.onOffSwitch.enabled = YES;
        
        return Cell;
        
    } else if (indexPath.section == 2) {
        
        if (indexPath.row == 0) {
            //eventConfigurationCellIdentifier
            CSREventConfigurationCell *Cell = [tableView dequeueReusableCellWithIdentifier:CSREventConfigurationCellIdentifier];
            if (!Cell) {
                Cell = [[CSREventConfigurationCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CSREventConfigurationCellIdentifier];
            }
            
            if ([_eventEntity.eventType isEqualToNumber:@1]) {
                Cell.eventConfigurationLabel.text = @"Light color event";
                NSData *colorData = [_eventEntity.eventValue subdataWithRange:NSMakeRange(0, _eventEntity.eventValue.length - 1)];
                NSData *intensityData = [_eventEntity.eventValue subdataWithRange:NSMakeRange(_eventEntity.eventValue.length - 1, 1)];
                int intensityInt;
                [intensityData getBytes:&intensityInt length:1];
                Cell.eventStateLabel.text = [NSString stringWithFormat:@"Colour %@", [[NSString alloc] initWithData:colorData encoding:NSUTF8StringEncoding]];
                Cell.eventSubStateLabel.text = [NSString stringWithFormat:@"Intensity %i%%", intensityInt];
                Cell.eventImageView.image = [UIImage imageNamed:@"colorPalette.png"];
                Cell.eventStateView.layer.cornerRadius = Cell.eventStateView.frame.size.width/2;
                //get color from nsdata
                NSString *colorString = [[NSString alloc] initWithData:colorData encoding:NSUTF8StringEncoding];
                NSString *colorValue = [CSRUtilities rgbFromColorName:colorString];
                [Cell.eventStateView setBackgroundColor:[CSRUtilities colorFromHex:colorValue]];
                
            } else if ([_eventEntity.eventType isEqualToNumber:@2]) {
                Cell.eventConfigurationLabel.text = @"Light power";
                Cell.eventSubStateLabel.text = @"Turn lights ON/OFF";
                Cell.eventStateLabel.hidden = YES;
                Cell.eventStateView.hidden = YES;
                Cell.eventImageView.image = [UIImage imageNamed:@"onOff.png"];

            } else if ([_eventEntity.eventType isEqualToNumber:@3]) {
                Cell.eventConfigurationLabel.text = @"Heating Event";
                Cell.eventSubStateLabel.text = [NSString stringWithFormat:@".02%f", _eventTemperature];
                Cell.eventStateLabel.hidden = YES;
                Cell.eventStateView.hidden = YES;
                Cell.eventImageView.image = [UIImage imageNamed:@"heater.png"];

            } else {
                
            }
        return Cell;
            
        } else {
           
            if ([self indexPathHasPicker:indexPath])
            {
                // the indexPath is the one containing the inline date picker
                Cell = [tableView dequeueReusableCellWithIdentifier:kDatePickerID];
                
                return Cell;
                
            }
            else if ([self indexPathHasDate:indexPath])
            {
                // the indexPath is one that contains the date information
                CSREventTimeCell *Cell = [tableView dequeueReusableCellWithIdentifier:CSREventTimeCellIdentifier];
                if (!Cell) {
                    Cell = [[CSREventTimeCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CSREventTimeCellIdentifier];
                }
                
                // if we have a date picker open whose cell is above the cell we want to update,
                // then we have one more cell than the model allows
                //
                NSInteger modelRow = indexPath.row;
                if (self.datePickerIndexPath != nil && self.datePickerIndexPath.row <= indexPath.row)
                {
                    modelRow--;
                }
                NSDictionary *itemData = self.dataArray[modelRow-1];
                
                Cell.eventTextLabel.text = @"Time";
                Cell.eventDateLabel.text = [itemData valueForKey:kDateKey];
                Cell.eventTimeLabel.text = _timeString;
                return Cell;

            }
            
            return nil;

        }
        
    } else if (indexPath.section == 3) {
        
        CSREventRepeatCell *Cell = [tableView dequeueReusableCellWithIdentifier:CSREventRepeatCellIdentifier];
        if (!Cell) {
            Cell = [[CSREventRepeatCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CSREventRepeatCellIdentifier];
        }
        Cell.repeatTextLabel.text = LOCALIZEDSTRING(@"Repeat");
        if (_repeatOnOff) {
            Cell.repeatSwitch.enabled = YES;
        } else {
            Cell.repeatSwitch.enabled = NO;
        }
        
        
        return Cell;
    }
    else if (indexPath.section == 4) {
        
        CSREventDevicesCell *Cell = [tableView dequeueReusableCellWithIdentifier:CSREventDevicesCellIdentifier];
        if (!Cell) {
            Cell = [[CSREventDevicesCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CSREventDevicesCellIdentifier];
        }
        Cell.selectionStyle = UITableViewCellSelectionStyleNone;
        CSRmeshDevice *meshDevice = [_allDevicesArray objectAtIndex:indexPath.row];
//        if ([meshDevice.appearanceValue  isEqual:@(CSRApperanceNameLight)]) {
            Cell.deviceImage.image = [UIImage imageNamed:@"light.png"];
//        }
        
        Cell.deviceNameLabel.text = meshDevice.name;
        if ([self hasEventGotDeviceWithId:meshDevice.deviceId]) {
            Cell.checkBox.checked = YES;
            
        } else {
            Cell.checkBox.checked = NO;
        }
        
        return Cell;
        
    } else {
        return nil;
    }
    return Cell;
}

- (void)toggleDatePickerForSelectedIndexPath:(NSIndexPath *)indexPath
{
    [_eventCreationTableView beginUpdates];
    
    NSArray *indexPaths = @[[NSIndexPath indexPathForRow:indexPath.row + 1 inSection:2]];
    
    // check if 'indexPath' has an attached date picker below it
    if ([self hasPickerForIndexPath:indexPath])
    {
        // found a picker below it, so remove it
        [_eventCreationTableView deleteRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationFade];
    }
    else
    {
        // didn't find a picker below it, so we should insert it
        [_eventCreationTableView insertRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationFade];
    }
    
    [_eventCreationTableView endUpdates];
}

- (void)displayInlineDatePickerForRowAtIndexPath:(NSIndexPath *)indexPath
{
    // display the date picker inline with the table content
    [_eventCreationTableView beginUpdates];
    
    BOOL before = NO;   // indicates if the date picker is below "indexPath", help us determine which row to reveal
    if ([self hasInlineDatePicker])
    {
        before = self.datePickerIndexPath.row < indexPath.row;
    }
    
    BOOL sameCellClicked = (self.datePickerIndexPath.row - 1 == indexPath.row);
    
    // remove any date picker cell if it exists
    if ([self hasInlineDatePicker])
    {
        [_eventCreationTableView deleteRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:self.datePickerIndexPath.row inSection:2]]
                              withRowAnimation:UITableViewRowAnimationFade];
        self.datePickerIndexPath = nil;
    }
    
    if (!sameCellClicked)
    {
        // hide the old date picker and display the new one
        NSInteger rowToReveal = (before ? indexPath.row - 1 : indexPath.row);
        NSIndexPath *indexPathToReveal = [NSIndexPath indexPathForRow:rowToReveal inSection:2];
        
        [self toggleDatePickerForSelectedIndexPath:indexPathToReveal];
        self.datePickerIndexPath = [NSIndexPath indexPathForRow:indexPathToReveal.row + 1 inSection:2];
    }
    
    // always deselect the row containing the start or end date
    [_eventCreationTableView deselectRowAtIndexPath:indexPath animated:YES];
    
    [_eventCreationTableView endUpdates];
    
    // inform our date picker of the current date to match the current cell
//    [self updateDatePicker];
}



- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    if (cell.reuseIdentifier == kCSREventTimeCellIdentifier) {
        
        [self displayInlineDatePickerForRowAtIndexPath:indexPath];

    }
    //For event on or off
    if (indexPath.section == 1) {
        
        CSREventOnOffCell *cell = (CSREventOnOffCell *)[tableView cellForRowAtIndexPath:indexPath];
        
        if (_onOffBool) {
            cell.onOffSwitch.on = YES;
            _onOffBool = NO;
        } else {
            cell.onOffSwitch.on = NO;
            _onOffBool = YES;
        }
    }
    
    if (cell.reuseIdentifier == kCSREventConfigurationCell) {
        
        
        [self performSegueWithIdentifier:@"eventControlSegue" sender:nil];
    }

    //For repaet action
    if (indexPath.section == 3) {
        
        CSREventRepeatCell *cell = (CSREventRepeatCell *)[tableView cellForRowAtIndexPath:indexPath];
        
        if (_repeatBool) {
            cell.repeatSwitch.on = NO;
            _repeatBool = NO;
        } else {
            cell.repeatSwitch.on = YES;
            _repeatBool = YES;
            [self performSegueWithIdentifier:@"repeatSegue" sender:nil];
        }
    }
    
    if (indexPath.section == 4) {
        
        CSREventDevicesCell *selectedCell = (CSREventDevicesCell*)[tableView cellForRowAtIndexPath:indexPath];
        selectedCell.checkBox.checked = !selectedCell.checkBox.checked;
        
        CSRDeviceEntity *deviceEntity = [_allDevicesArray objectAtIndex:indexPath.row];
        
        if ([_selectedDevicesArray containsObject:deviceEntity.deviceId]) {
            [_selectedDevicesArray removeObject:deviceEntity.deviceId];

        } else {
            [_selectedDevicesArray addObject:deviceEntity.deviceId];
        }
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

}


#pragma mark - <UIPopoverPresentationControllerDelegate>

- (UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller
{
    // Return no adaptive presentation style, use default presentation behaviour
    return UIModalPresentationNone;
}

- (BOOL)popoverPresentationControllerShouldDismissPopover:(UIPopoverPresentationController *)popoverPresentationController
{
    return NO;
}


#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:@"repeatSegue"]) {
        CSREventTimeSelectorVC *vc = segue.destinationViewController;
        vc.popoverPresentationController.delegate = self;
        vc.popoverPresentationController.containerView.superview.layer.cornerRadius = 0;
        vc.preferredContentSize = CGSizeMake(self.view.frame.size.width - 20., 175.);
        
        vc.eventsDelegate = self;
    }
    
    if ([segue.identifier isEqualToString:@"eventControlSegue"]) {
        
        //Take a event type
        CSREventControlVC *vc = segue.destinationViewController;
        vc.typeOfEvent = [_eventEntity.eventType integerValue];
        
    }
}


#pragma mark - Actions

/*! User chose to change the date by changing the values inside the UIDatePicker.
 
 @param sender The sender for this action: UIDatePicker.
 */
- (IBAction)dateAction:(id)sender
{
    NSIndexPath *targetedCellIndexPath = nil;
    
    if ([self hasInlineDatePicker])
    {
        // inline date picker: update the cell's date "above" the date picker cell
        //
        targetedCellIndexPath = [NSIndexPath indexPathForRow:self.datePickerIndexPath.row - 1 inSection:2];
    }
    else
    {
        // external date picker: update the current "selected" cell's date
        targetedCellIndexPath = [_eventCreationTableView indexPathForSelectedRow];
    }
    
    CSREventTimeCell *cell = [_eventCreationTableView cellForRowAtIndexPath:targetedCellIndexPath];
    UIDatePicker *targetedDatePicker = sender;
    
    // update our data model
    NSMutableDictionary *itemData = self.dataArray[targetedCellIndexPath.row - 1];
    [itemData setValue:targetedDatePicker.date forKey:kDateKey];
    
    // update the cell's date string
    cell.eventDateLabel.text = [self.dateFormatter stringFromDate:targetedDatePicker.date];
}


- (IBAction)saveEventAction:(id)sender {
    
    _eventEntity.eventName = _eventNameString;
    _eventEntity.eventid = [[CSRDatabaseManager sharedInstance] getNextFreeIDOfType:@"CSREventEntity"];
    _eventEntity.eventType = @(_typeOfEvent);
    
    _eventEntity.eventActive = [NSNumber numberWithBool:_onOffBool];
    
    //adding DeviceEntity as relation to EventEntity
    __block CSRDeviceEntity *localdeviceEntity;
    [_selectedDevicesArray enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSNumber *localdeviceId = (NSNumber *)obj;
        localdeviceEntity = [[CSRDatabaseManager sharedInstance] getDeviceEntityWithId:localdeviceId];
        [_eventEntity addDevicesObject:localdeviceEntity];
        
    }];
    
    if (_typeOfEvent == 1) {
        
        NSString *colorName = [CSRUtilities colorNameForRGB:[CSRUtilities rgbFromColor:_eventColor]];
        NSString *intenString = [NSString stringWithFormat:@"%.0f",_intensityFloat *100];
        
        NSMutableData *mutableData = [[NSMutableData alloc] initWithData:[colorName dataUsingEncoding:NSUTF8StringEncoding]];
        [mutableData appendData:[intenString dataUsingEncoding:NSUTF8StringEncoding]];
        
        _eventEntity.eventValue = [mutableData copy];
        
    } else if (_typeOfEvent == 2) {
        
        NSInteger powerInt = @(_eventOnOff).integerValue;
        NSData *data = [NSData dataWithBytes: &powerInt length: sizeof(powerInt)];
        _eventEntity.eventValue = data;
        
    } else if (_typeOfEvent == 3) {
        
        NSData *data = [NSData dataWithBytes:&_eventTemperature length:sizeof(_eventTemperature)];
        _eventEntity.eventValue = data;
        
    }
    
    _eventsManager = [[CSREventsManager alloc] initWithData:_eventEntity];
    
    //To get rid of retain count warning
    __weak typeof(self) weakSelf = self;
    _eventsManager.errorHandler = ^(NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            
            [weakSelf handleError:error];
        });
    };
    
    
    [[CSRAppStateManager sharedInstance].selectedPlace addEventsObject:_eventEntity];
    [[CSRDatabaseManager sharedInstance] saveContext];
    
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRRefreshNotification object:self userInfo:nil];
    
    [self dismissViewControllerAnimated:YES completion:nil];
    
}

- (IBAction)closeEventAction:(id)sender {
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)deleteEventAction:(id)sender {
    
    if(_eventEntity) {
        [[CSRDevicesManager sharedInstance] removeEventWithEventId:_eventEntity.eventid];
        [[CSRDatabaseManager sharedInstance].managedObjectContext deleteObject:_eventEntity];
    }
    
    //Showing a Activity Indicator for a second, to do operation
    UIActivityIndicatorView *spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    [self.view addSubview:spinner];
    spinner.center = CGPointMake(self.view.frame.size.width / 2, self.view.frame.size.height / 2);
    [spinner startAnimating];
    
    [self performSelector:@selector(dismissViewController:) withObject:spinner afterDelay:1.5];
    
}

- (void) dismissViewController:(UIActivityIndicatorView*)spin
{
    [self.presentingViewController.presentingViewController dismissViewControllerAnimated:YES completion:^{
        [spin stopAnimating];
    }];
    
}

#pragma mark - Delegate Callbacks

- (void) repeatEveryHour:(NSNumber *)hour ofDays:(NSData *)data {
    
    //got the data now save to core data
    _weekDaysData = data;
    _hourField = hour;
}


#pragma mark - Helper method

- (BOOL)hasEventGotDeviceWithId:(NSNumber *)deviceId
{
    __block BOOL deviceFound = NO;
    
    [_allDevicesArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        
        if ([((CSRDeviceEntity *)obj).deviceId intValue] == [deviceId intValue]) {
            
            deviceFound = YES;
            
            *stop = YES;
            
        }
        
    }];
    
    return deviceFound;
}


#pragma mark --
#pragma marl UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    _eventNameString = textField.text;
    [textField resignFirstResponder];
    
    return YES;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSCurrentLocaleDidChangeNotification
                                                  object:nil];
}

- (void)handleError:(NSError *)error
{
    NSString *errorMessage = [error localizedDescription];
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Cannot Send the data"
                                                                   message:errorMessage
                                                            preferredStyle:UIAlertControllerStyleActionSheet];
    UIAlertAction *OKAction = [UIAlertAction actionWithTitle:@"OK"
                                                       style:UIAlertActionStyleDefault
                                                     handler:^(UIAlertAction *action) {
                                                         // dissmissal of alert completed
                                                     }];
    
    [alert addAction:OKAction];
    [self presentViewController:alert animated:YES completion:nil];
}



@end
