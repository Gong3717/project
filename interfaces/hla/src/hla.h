// Copyright (c) 2001-2009, Scalable Network Technologies, Inc.  All Rights Reserved.
//                          6100 Center Drive
//                          Suite 1250
//                          Los Angeles, CA 90045
//                          sales@scalable-networks.com
//
// This source code is licensed, not sold, and is subject to a written
// license agreement.  Among other things, no portion of this source
// code may be copied, transmitted, disclosed, displayed, distributed,
// translated, used as the basis for a derivative work, or used, in
// whole or in part, for any program or purpose other than its intended
// use in compliance with the license agreement as part of the QualNet
// software.  This source code and certain of the algorithms contained
// within it are confidential trade secrets of Scalable Network
// Technologies, Inc. and may not be used as the basis for any other
// software, hardware, product or service.

#ifndef HLA_H
#define HLA_H

void
HlaReadHlaParameter(NodeInput* nodeInput);

bool
HlaActive(const NodeInput* nodeInput);

bool
HlaIsActive();

void
HlaInit(EXTERNAL_Interface* iface, NodeInput* nodeInput);

void
HlaInitNodes(EXTERNAL_Interface* iface, NodeInput* nodeInput);

void
HlaReceive(EXTERNAL_Interface* iface);

void
HlaProcessEvent(Node* node, Message* msg);

void
HlaFinalize(EXTERNAL_Interface* iface);

void
HlaUpdateMetric(
    unsigned nodeId,
    const MetricData& metric,
    void* metricValue,
    clocktype updateTime);

#ifdef MILITARY_RADIOS_LIB
void
HlaSendRtssNotificationIfNodeIsHlaEnabled(Node* node);
#endif /* MILITARY_RADIOS_LIB */

#endif /* HLA_H */
