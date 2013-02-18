/*
 * ManualAdaptation.cpp
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "ManualAdaptation.h"

using namespace dash::mpd;
using namespace libdash::framework::adaptation;

ManualAdaptation::ManualAdaptation          (dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IMPD *mpd) : 
                  AbstractAdaptationLogic   (adaptationSet, mpd),
                  adaptationSet             (adaptationSet),
                  mpd                       (mpd),
                  segmentNumber             (0)
{
    this->baseurls.push_back(this->mpd->GetBaseUrls().at(0));
    this->representation = this->adaptationSet->GetRepresentation().at(0);
}
ManualAdaptation::~ManualAdaptation         ()
{
}

MediaObject*    ManualAdaptation::GetSegment            ()
{
    ISegment *seg = NULL;

    if(this->segmentNumber >= this->representation->GetSegmentList()->GetSegmentURLs().size() + 1)
        return NULL;

    if(this->segmentNumber == 0)
    {
        seg = this->representation->GetSegmentBase()->GetInitialization()->ToSegment(this->baseurls);
    }   
    else
    {
        seg = this->representation->GetSegmentList()->GetSegmentURLs().at(this->segmentNumber - 1)->ToMediaSegment(this->baseurls);
    }
    
    MediaObject *media = new MediaObject(seg, this->representation);
    this->segmentNumber++;
    return media;
}
uint32_t        ManualAdaptation::GetPosition           ()
{
    return this->segmentNumber;
}
void            ManualAdaptation::SetPosition           (uint32_t segmentNumber)
{
    this->segmentNumber = segmentNumber;
}
void            ManualAdaptation::SetRepresentation     (dash::mpd::IRepresentation *representation)
{
    this->representation = representation;
}