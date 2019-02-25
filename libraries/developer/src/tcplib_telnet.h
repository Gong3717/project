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

/*
 *
 * Ported from TCPLIB. Header file of telnet.c.
 */

/*
 * Copyright (c) 1991 University of Southern California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Southern California. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
*/

static struct entry pktsize[] =
{
    { 1.000000F, 0.628000F },
    { 2.000000F, 0.749000F },
    { 3.000000F, 0.790000F },
    { 4.000000F, 0.802000F },
    { 5.000000F, 0.815000F },
    { 6.000000F, 0.822000F },
    { 7.000000F, 0.828000F },
    { 8.000000F, 0.837000F },
    { 9.000000F, 0.843000F },
    { 10.000000F, 0.846000F },
    { 11.000000F, 0.850000F },
    { 12.000000F, 0.853000F },
    { 13.000000F, 0.857000F },
    { 14.000000F, 0.859000F },
    { 15.000000F, 0.862000F },
    { 16.000000F, 0.864000F },
    { 17.000000F, 0.866000F },
    { 18.000000F, 0.869000F },
    { 19.000000F, 0.870000F },
    { 20.000000F, 0.872000F },
    { 21.000000F, 0.873000F },
    { 22.000000F, 0.875000F },
    { 23.000000F, 0.876000F },
    { 24.000000F, 0.878000F },
    { 25.000000F, 0.879000F },
    { 26.000000F, 0.881000F },
    { 27.000000F, 0.882000F },
    { 28.000000F, 0.884000F },
    { 29.000000F, 0.885000F },
    { 30.000000F, 0.887000F },
    { 31.000000F, 0.888000F },
    { 32.000000F, 0.889000F },
    { 33.000000F, 0.890000F },
    { 34.000000F, 0.891000F },
    { 35.000000F, 0.892000F },
    { 36.000000F, 0.895000F },
    { 37.000000F, 0.897000F },
    { 38.000000F, 0.898000F },
    { 39.000000F, 0.899000F },
    { 40.000000F, 0.901000F },
    { 41.000000F, 0.902000F },
    { 42.000000F, 0.904000F },
    { 43.000000F, 0.905000F },
    { 44.000000F, 0.906000F },
    { 45.000000F, 0.907000F },
    { 46.000000F, 0.908000F },
    { 47.000000F, 0.909000F },
    { 48.000000F, 0.910000F },
    { 49.000000F, 0.911000F },
    { 50.000000F, 0.912000F },
    { 51.000000F, 0.913000F },
    { 53.000000F, 0.916000F },
    { 54.000000F, 0.917000F },
    { 55.000000F, 0.918000F },
    { 57.000000F, 0.919000F },
    { 58.000000F, 0.920000F },
    { 59.000000F, 0.921000F },
    { 60.000000F, 0.922000F },
    { 62.000000F, 0.923000F },
    { 63.000000F, 0.924000F },
    { 64.000000F, 0.925000F },
    { 66.000000F, 0.926000F },
    { 68.000000F, 0.927000F },
    { 69.000000F, 0.928000F },
    { 71.000000F, 0.929000F },
    { 72.000000F, 0.930000F },
    { 74.000000F, 0.931000F },
    { 76.000000F, 0.932000F },
    { 78.000000F, 0.933000F },
    { 79.000000F, 0.934000F },
    { 80.000000F, 0.935000F },
    { 81.000000F, 0.936000F },
    { 83.000000F, 0.943000F },
    { 86.000000F, 0.944000F },
    { 90.000000F, 0.945000F },
    { 95.000000F, 0.946000F },
    { 99.000000F, 0.947000F },
    { 105.000000F, 0.948000F },
    { 110.000000F, 0.949000F },
    { 114.000000F, 0.950000F },
    { 121.000000F, 0.951000F },
    { 127.000000F, 0.952000F },
    { 133.000000F, 0.953000F },
    { 142.000000F, 0.954000F },
    { 150.000000F, 0.955000F },
    { 161.000000F, 0.956000F },
    { 174.000000F, 0.957000F },
    { 187.000000F, 0.958000F },
    { 194.000000F, 0.959000F },
    { 207.000000F, 0.960000F },
    { 220.000000F, 0.961000F },
    { 233.000000F, 0.962000F },
    { 243.000000F, 0.963000F },
    { 254.000000F, 0.964000F },
    { 261.000000F, 0.965000F },
    { 275.000000F, 0.966000F },
    { 290.000000F, 0.967000F },
    { 307.000000F, 0.968000F },
    { 325.000000F, 0.969000F },
    { 336.000000F, 0.970000F },
    { 356.000000F, 0.971000F },
    { 375.000000F, 0.972000F },
    { 398.000000F, 0.973000F },
    { 417.000000F, 0.974000F },
    { 439.000000F, 0.975000F },
    { 464.000000F, 0.976000F },
    { 487.000000F, 0.977000F },
    { 505.000000F, 0.978000F },
    { 510.000000F, 0.979000F },
    { 511.000000F, 0.980000F },
    { 535.000000F, 0.997000F },
    { 621.000000F, 0.999000F },
    { 1024.000000F, 1.000000F }
};

static struct entry interarrival[] =
{
    { 0.600000F, 0.000000F },
    { 0.800000F, 0.001000F },
    { 0.900000F, 0.002000F },
    { 1.000000F, 0.003000F },
    { 1.100000F, 0.008000F },
    { 1.200000F, 0.011000F },
    { 1.300000F, 0.013000F },
    { 1.400000F, 0.014000F },
    { 1.500000F, 0.016000F },
    { 1.600000F, 0.017000F },
    { 1.700000F, 0.018000F },
    { 1.800000F, 0.020000F },
    { 1.900000F, 0.021000F },
    { 2.000000F, 0.022000F },
    { 2.100000F, 0.023000F },
    { 2.200000F, 0.024000F },
    { 2.300000F, 0.026000F },
    { 2.400000F, 0.027000F },
    { 2.500000F, 0.028000F },
    { 2.600000F, 0.029000F },
    { 2.700000F, 0.030000F },
    { 2.800000F, 0.031000F },
    { 2.900000F, 0.032000F },
    { 3.000000F, 0.033000F },
    { 3.100000F, 0.034000F },
    { 3.300000F, 0.035000F },
    { 3.400000F, 0.036000F },
    { 3.600000F, 0.037000F },
    { 3.800000F, 0.038000F },
    { 4.100000F, 0.039000F },
    { 4.400000F, 0.040000F },
    { 4.900000F, 0.041000F },
    { 5.400000F, 0.042000F },
    { 6.200000F, 0.043000F },
    { 7.200000F, 0.044000F },
    { 8.600000F, 0.045000F },
    { 10.000000F, 0.046000F },
    { 12.500000F, 0.047000F },
    { 14.500000F, 0.048000F },
    { 16.500000F, 0.049000F },
    { 18.000000F, 0.050000F },
    { 19.500000F, 0.051000F },
    { 21.000000F, 0.052000F },
    { 22.000000F, 0.053000F },
    { 23.000000F, 0.054000F },
    { 24.000000F, 0.055000F },
    { 25.000000F, 0.056000F },
    { 26.000000F, 0.057000F },
    { 27.000000F, 0.059000F },
    { 28.000000F, 0.060000F },
    { 29.000000F, 0.061000F },
    { 30.000000F, 0.062000F },
    { 31.000000F, 0.063000F },
    { 32.000000F, 0.064000F },
    { 34.000000F, 0.065000F },
    { 35.000000F, 0.066000F },
    { 36.000000F, 0.067000F },
    { 37.000000F, 0.068000F },
    { 38.000000F, 0.069000F },
    { 39.000000F, 0.070000F },
    { 40.000000F, 0.071000F },
    { 42.000000F, 0.073000F },
    { 43.000000F, 0.074000F },
    { 44.000000F, 0.075000F },
    { 45.000000F, 0.076000F },
    { 46.000000F, 0.077000F },
    { 47.000000F, 0.078000F },
    { 48.000000F, 0.079000F },
    { 49.000000F, 0.080000F },
    { 50.000000F, 0.081000F },
    { 52.000000F, 0.082000F },
    { 53.000000F, 0.083000F },
    { 54.000000F, 0.084000F },
    { 55.000000F, 0.085000F },
    { 56.000000F, 0.086000F },
    { 57.000000F, 0.087000F },
    { 58.000000F, 0.088000F },
    { 59.000000F, 0.090000F },
    { 60.000000F, 0.091000F },
    { 61.000000F, 0.093000F },
    { 62.000000F, 0.094000F },
    { 63.000000F, 0.096000F },
    { 64.000000F, 0.098000F },
    { 65.000000F, 0.099000F },
    { 66.000000F, 0.101000F },
    { 67.000000F, 0.103000F },
    { 68.000000F, 0.104000F },
    { 69.000000F, 0.106000F },
    { 70.000000F, 0.107000F },
    { 71.000000F, 0.108000F },
    { 72.000000F, 0.110000F },
    { 73.000000F, 0.111000F },
    { 74.000000F, 0.113000F },
    { 75.000000F, 0.114000F },
    { 76.000000F, 0.116000F },
    { 77.000000F, 0.118000F },
    { 78.000000F, 0.120000F },
    { 79.000000F, 0.123000F },
    { 80.000000F, 0.125000F },
    { 81.000000F, 0.128000F },
    { 82.000000F, 0.130000F },
    { 83.000000F, 0.131000F },
    { 84.000000F, 0.133000F },
    { 85.000000F, 0.135000F },
    { 86.000000F, 0.136000F },
    { 87.000000F, 0.138000F },
    { 88.000000F, 0.140000F },
    { 89.000000F, 0.142000F },
    { 90.000000F, 0.145000F },
    { 91.000000F, 0.147000F },
    { 92.000000F, 0.150000F },
    { 93.000000F, 0.152000F },
    { 94.000000F, 0.155000F },
    { 95.000000F, 0.157000F },
    { 96.000000F, 0.159000F },
    { 97.000000F, 0.162000F },
    { 98.000000F, 0.164000F },
    { 99.000000F, 0.167000F },
    { 100.000000F, 0.179000F },
    { 105.000000F, 0.189000F },
    { 110.000000F, 0.199000F },
    { 115.000000F, 0.211000F },
    { 120.000000F, 0.222000F },
    { 125.000000F, 0.232000F },
    { 130.000000F, 0.241000F },
    { 135.000000F, 0.252000F },
    { 140.000000F, 0.263000F },
    { 145.000000F, 0.274000F },
    { 150.000000F, 0.285000F },
    { 155.000000F, 0.301000F },
    { 160.000000F, 0.315000F },
    { 165.000000F, 0.327000F },
    { 170.000000F, 0.338000F },
    { 175.000000F, 0.352000F },
    { 180.000000F, 0.366000F },
    { 185.000000F, 0.378000F },
    { 190.000000F, 0.391000F },
    { 195.000000F, 0.410000F },
    { 200.000000F, 0.428000F },
    { 205.000000F, 0.441000F },
    { 210.000000F, 0.452000F },
    { 215.000000F, 0.463000F },
    { 220.000000F, 0.474000F },
    { 225.000000F, 0.484000F },
    { 230.000000F, 0.494000F },
    { 235.000000F, 0.506000F },
    { 240.000000F, 0.517000F },
    { 245.000000F, 0.525000F },
    { 250.000000F, 0.533000F },
    { 255.000000F, 0.541000F },
    { 260.000000F, 0.549000F },
    { 265.000000F, 0.555000F },
    { 270.000000F, 0.563000F },
    { 275.000000F, 0.570000F },
    { 280.000000F, 0.576000F },
    { 285.000000F, 0.582000F },
    { 290.000000F, 0.587000F },
    { 295.000000F, 0.593000F },
    { 300.000000F, 0.599000F },
    { 305.000000F, 0.604000F },
    { 310.000000F, 0.608000F },
    { 315.000000F, 0.613000F },
    { 320.000000F, 0.618000F },
    { 325.000000F, 0.622000F },
    { 330.000000F, 0.626000F },
    { 335.000000F, 0.630000F },
    { 340.000000F, 0.634000F },
    { 345.000000F, 0.637000F },
    { 350.000000F, 0.641000F },
    { 355.000000F, 0.645000F },
    { 360.000000F, 0.649000F },
    { 365.000000F, 0.652000F },
    { 370.000000F, 0.656000F },
    { 375.000000F, 0.660000F },
    { 380.000000F, 0.664000F },
    { 385.000000F, 0.669000F },
    { 390.000000F, 0.674000F },
    { 395.000000F, 0.680000F },
    { 400.000000F, 0.687000F },
    { 405.000000F, 0.691000F },
    { 410.000000F, 0.695000F },
    { 415.000000F, 0.699000F },
    { 420.000000F, 0.702000F },
    { 425.000000F, 0.705000F },
    { 430.000000F, 0.708000F },
    { 435.000000F, 0.711000F },
    { 440.000000F, 0.714000F },
    { 445.000000F, 0.716000F },
    { 450.000000F, 0.718000F },
    { 455.000000F, 0.721000F },
    { 460.000000F, 0.723000F },
    { 465.000000F, 0.725000F },
    { 470.000000F, 0.727000F },
    { 475.000000F, 0.729000F },
    { 480.000000F, 0.732000F },
    { 485.000000F, 0.734000F },
    { 490.000000F, 0.735000F },
    { 495.000000F, 0.737000F },
    { 500.000000F, 0.741000F },
    { 510.000000F, 0.745000F },
    { 520.000000F, 0.748000F },
    { 530.000000F, 0.751000F },
    { 540.000000F, 0.754000F },
    { 550.000000F, 0.758000F },
    { 560.000000F, 0.761000F },
    { 570.000000F, 0.764000F },
    { 580.000000F, 0.767000F },
    { 590.000000F, 0.770000F },
    { 600.000000F, 0.773000F },
    { 610.000000F, 0.776000F },
    { 620.000000F, 0.778000F },
    { 630.000000F, 0.781000F },
    { 640.000000F, 0.783000F },
    { 650.000000F, 0.785000F },
    { 660.000000F, 0.787000F },
    { 670.000000F, 0.790000F },
    { 680.000000F, 0.792000F },
    { 690.000000F, 0.794000F },
    { 700.000000F, 0.796000F },
    { 710.000000F, 0.798000F },
    { 720.000000F, 0.800000F },
    { 730.000000F, 0.802000F },
    { 740.000000F, 0.804000F },
    { 750.000000F, 0.806000F },
    { 760.000000F, 0.808000F },
    { 770.000000F, 0.809000F },
    { 780.000000F, 0.811000F },
    { 790.000000F, 0.813000F },
    { 800.000000F, 0.815000F },
    { 810.000000F, 0.817000F },
    { 820.000000F, 0.819000F },
    { 830.000000F, 0.820000F },
    { 840.000000F, 0.822000F },
    { 850.000000F, 0.823000F },
    { 860.000000F, 0.825000F },
    { 870.000000F, 0.827000F },
    { 880.000000F, 0.828000F },
    { 890.000000F, 0.830000F },
    { 900.000000F, 0.832000F },
    { 910.000000F, 0.833000F },
    { 920.000000F, 0.835000F },
    { 930.000000F, 0.836000F },
    { 940.000000F, 0.837000F },
    { 950.000000F, 0.838000F },
    { 960.000000F, 0.840000F },
    { 970.000000F, 0.841000F },
    { 980.000000F, 0.843000F },
    { 990.000000F, 0.844000F },
    { 1000.000000F, 0.856000F },
    { 1100.000000F, 0.866000F },
    { 1200.000000F, 0.875000F },
    { 1300.000000F, 0.882000F },
    { 1400.000000F, 0.889000F },
    { 1500.000000F, 0.895000F },
    { 1600.000000F, 0.901000F },
    { 1700.000000F, 0.905000F },
    { 1800.000000F, 0.910000F },
    { 1900.000000F, 0.914000F },
    { 2000.000000F, 0.917000F },
    { 2100.000000F, 0.921000F },
    { 2200.000000F, 0.924000F },
    { 2300.000000F, 0.926000F },
    { 2400.000000F, 0.929000F },
    { 2500.000000F, 0.931000F },
    { 2600.000000F, 0.933000F },
    { 2700.000000F, 0.935000F },
    { 2800.000000F, 0.937000F },
    { 2900.000000F, 0.939000F },
    { 3000.000000F, 0.941000F },
    { 3100.000000F, 0.942000F },
    { 3200.000000F, 0.944000F },
    { 3300.000000F, 0.945000F },
    { 3400.000000F, 0.947000F },
    { 3500.000000F, 0.948000F },
    { 3600.000000F, 0.949000F },
    { 3700.000000F, 0.950000F },
    { 3800.000000F, 0.951000F },
    { 3900.000000F, 0.952000F },
    { 4000.000000F, 0.953000F },
    { 4200.000000F, 0.955000F },
    { 4300.000000F, 0.956000F },
    { 4400.000000F, 0.957000F },
    { 4500.000000F, 0.958000F },
    { 4700.000000F, 0.959000F },
    { 4800.000000F, 0.960000F },
    { 4900.000000F, 0.961000F },
    { 5000.000000F, 0.966000F },
    { 6000.000000F, 0.971000F },
    { 7000.000000F, 0.974000F },
    { 8000.000000F, 0.977000F },
    { 9000.000000F, 0.979000F },
    { 10000.000000F, 0.981000F },
    { 11000.000000F, 0.983000F },
    { 12000.000000F, 0.984000F },
    { 13000.000000F, 0.985000F },
    { 14000.000000F, 0.986000F },
    { 15000.000000F, 0.987000F },
    { 17000.000000F, 0.988000F },
    { 18000.000000F, 0.989000F },
    { 20000.000000F, 0.990000F },
    { 22000.000000F, 0.991000F },
    { 24000.000000F, 0.992000F },
    { 28000.000000F, 0.993000F },
    { 32000.000000F, 0.994000F },
    { 38000.000000F, 0.995000F },
    { 46000.000000F, 0.996000F },
    { 59000.000000F, 0.997000F },
    { 60000.000000F, 0.998000F },
    { 240000.000000F, 0.999000F },
    { 1140000.000000F, 1.000000F }
};

static struct entry duration[] =
{
    { 1.000000F, 0.026000F },
    { 100.000000F, 0.027000F },
    { 200.000000F, 0.029000F },
    { 300.000000F, 0.030000F },
    { 400.000000F, 0.032000F },
    { 500.000000F, 0.035000F },
    { 600.000000F, 0.037000F },
    { 700.000000F, 0.038000F },
    { 800.000000F, 0.039000F },
    { 1000.000000F, 0.041000F },
    { 1200.000000F, 0.042000F },
    { 1400.000000F, 0.044000F },
    { 1500.000000F, 0.046000F },
    { 1600.000000F, 0.047000F },
    { 1700.000000F, 0.049000F },
    { 1800.000000F, 0.051000F },
    { 1900.000000F, 0.053000F },
    { 2000.000000F, 0.054000F },
    { 2100.000000F, 0.055000F },
    { 2300.000000F, 0.057000F },
    { 2400.000000F, 0.058000F },
    { 2500.000000F, 0.060000F },
    { 2600.000000F, 0.061000F },
    { 2700.000000F, 0.064000F },
    { 2800.000000F, 0.065000F },
    { 2900.000000F, 0.066000F },
    { 3000.000000F, 0.068000F },
    { 3100.000000F, 0.069000F },
    { 3200.000000F, 0.071000F },
    { 3300.000000F, 0.073000F },
    { 3400.000000F, 0.074000F },
    { 3500.000000F, 0.075000F },
    { 3600.000000F, 0.076000F },
    { 3900.000000F, 0.077000F },
    { 4000.000000F, 0.078000F },
    { 4100.000000F, 0.080000F },
    { 4300.000000F, 0.081000F },
    { 4500.000000F, 0.083000F },
    { 4800.000000F, 0.084000F },
    { 5100.000000F, 0.085000F },
    { 5200.000000F, 0.086000F },
    { 5300.000000F, 0.087000F },
    { 5600.000000F, 0.088000F },
    { 5700.000000F, 0.089000F },
    { 5800.000000F, 0.091000F },
    { 6000.000000F, 0.093000F },
    { 6400.000000F, 0.095000F },
    { 6500.000000F, 0.097000F },
    { 6600.000000F, 0.098000F },
    { 6900.000000F, 0.100000F },
    { 7000.000000F, 0.101000F },
    { 7400.000000F, 0.102000F },
    { 7500.000000F, 0.103000F },
    { 7900.000000F, 0.104000F },
    { 8000.000000F, 0.109000F },
    { 8500.000000F, 0.111000F },
    { 9000.000000F, 0.114000F },
    { 9500.000000F, 0.115000F },
    { 10000.000000F, 0.118000F },
    { 10500.000000F, 0.120000F },
    { 11000.000000F, 0.121000F },
    { 11500.000000F, 0.122000F },
    { 12000.000000F, 0.126000F },
    { 12500.000000F, 0.128000F },
    { 13000.000000F, 0.132000F },
    { 13500.000000F, 0.136000F },
    { 14000.000000F, 0.141000F },
    { 15000.000000F, 0.144000F },
    { 16000.000000F, 0.148000F },
    { 17000.000000F, 0.153000F },
    { 18000.000000F, 0.156000F },
    { 19000.000000F, 0.162000F },
    { 20000.000000F, 0.169000F },
    { 21000.000000F, 0.176000F },
    { 22000.000000F, 0.182000F },
    { 23000.000000F, 0.186000F },
    { 24000.000000F, 0.193000F },
    { 26000.000000F, 0.202000F },
    { 28000.000000F, 0.209000F },
    { 30000.000000F, 0.214000F },
    { 32000.000000F, 0.220000F },
    { 34000.000000F, 0.228000F },
    { 36000.000000F, 0.233000F },
    { 38000.000000F, 0.244000F },
    { 40000.000000F, 0.252000F },
    { 42000.000000F, 0.259000F },
    { 44000.000000F, 0.266000F },
    { 46000.000000F, 0.270000F },
    { 48000.000000F, 0.275000F },
    { 50000.000000F, 0.280000F },
    { 52000.000000F, 0.284000F },
    { 54000.000000F, 0.288000F },
    { 56000.000000F, 0.293000F },
    { 58000.000000F, 0.299000F },
    { 60000.000000F, 0.324000F },
    { 65000.000000F, 0.332000F },
    { 70000.000000F, 0.347000F },
    { 75000.000000F, 0.363000F },
    { 80000.000000F, 0.371000F },
    { 85000.000000F, 0.380000F },
    { 90000.000000F, 0.404000F },
    { 105000.000000F, 0.427000F },
    { 120000.000000F, 0.445000F },
    { 135000.000000F, 0.463000F },
    { 150000.000000F, 0.480000F },
    { 165000.000000F, 0.494000F },
    { 180000.000000F, 0.513000F },
    { 210000.000000F, 0.531000F },
    { 240000.000000F, 0.556000F },
    { 270000.000000F, 0.576000F },
    { 300000.000000F, 0.604000F },
    { 360000.000000F, 0.640000F },
    { 420000.000000F, 0.664000F },
    { 480000.000000F, 0.678000F },
    { 540000.000000F, 0.697000F },
    { 600000.000000F, 0.715000F },
    { 660000.000000F, 0.731000F },
    { 720000.000000F, 0.743000F },
    { 780000.000000F, 0.754000F },
    { 840000.000000F, 0.779000F },
    { 960000.000000F, 0.799000F },
    { 1080000.000000F, 0.817000F },
    { 1200000.000000F, 0.828000F },
    { 1320000.000000F, 0.841000F },
    { 1440000.000000F, 0.854000F },
    { 1560000.000000F, 0.867000F },
    { 1680000.000000F, 0.878000F },
    { 1800000.000000F, 0.885000F },
    { 1920000.000000F, 0.897000F },
    { 2040000.000000F, 0.904000F },
    { 2160000.000000F, 0.907000F },
    { 2280000.000000F, 0.914000F },
    { 2400000.000000F, 0.920000F },
    { 2520000.000000F, 0.928000F },
    { 2640000.000000F, 0.931000F },
    { 2760000.000000F, 0.938000F },
    { 2880000.000000F, 0.944000F },
    { 3000000.000000F, 0.949000F },
    { 3120000.000000F, 0.951000F },
    { 3240000.000000F, 0.955000F },
    { 3360000.000000F, 0.958000F },
    { 3480000.000000F, 0.959000F },
    { 3600000.000000F, 0.967000F },
    { 3900000.000000F, 0.971000F },
    { 4200000.000000F, 0.974000F },
    { 4800000.000000F, 0.976000F },
    { 5100000.000000F, 0.980000F },
    { 5700000.000000F, 0.983000F },
    { 6000000.000000F, 0.985000F },
    { 6300000.000000F, 0.987000F },
    { 6600000.000000F, 0.988000F },
    { 6900000.000000F, 0.989000F },
    { 7200000.000000F, 1.000000F }
};

static struct histmap telnet_histmap[] =
{
    { "pktsize", 113 },
    { "interarrival", 310 },
    { "duration", 153 }
};

