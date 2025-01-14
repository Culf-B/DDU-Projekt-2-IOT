let dataDict = {};
let pie, bar;
let rendered = false;

let recommendedValues = {"N": [40, 60], "P": [52.2, 100], "K": [127.5, 200]};

function setup() 
{
  createCanvas(400, 400);
  loadJSON('Dictionary.json', ConvertJsonToDict);

  InputChoice = createInput();
  InputChoice.size(250, 30);
  InputChoice.attribute('placeholder', 'Choose chart type (write in all lowercase)');
}

function draw() 
{
  background(220);
  rendered = false;
  if(!rendered && Object.keys(dataDict).length > 0 && str(InputChoice.value()) == "piechart") 
  {
    pie = new Piechart(dataDict);
    pie.display();
    rendered = true;
  }
  if(!rendered && Object.keys(dataDict).length > 0 && str(InputChoice.value()) == "barchart") 
    {
      bar = new Barchart(dataDict, recommendedValues);
      bar.display();
      rendered = true;
    }
}

function ConvertJsonToDict(jsonData) 
{
  dataDict = jsonData;
  RefineDict(dataDict);
}

function RefineDict(dict) 
{
  for (let key in dict) 
  {
    dict[key] = dict[key].map(value => Math.round(value * 100) / 100);
  }
}

class Piechart 
{
  constructor(dict) 
  {
    this.dict = dict;
    this.labels = Object.keys(dict);
    this.sizes = this.calculateSizes();
    this.colors = this.assignColors();
  }

  calculateSizes() 
  {
    let sizes = [];
    for (let key in this.dict) 
    {
      let values = this.dict[key];
      let avg = values.reduce((a, b) => a + b, 0) / values.length;
      sizes.push(avg);
    }
    return sizes;
  }

  assignColors() 
  {
    return this.sizes.map(size => 
    {
      let percentage = size / this.sizes.reduce((a, b) => a + b, 0);
      let hue = percentage * 360;
      colorMode(HSB, 360, 100, 100);
      return color(hue, 80, 100);
    });
  }

  display() 
  {
    let total = this.sizes.reduce((a, b) => a + b, 0);
    let lastAngle = 0;

    for (let i = 0; i < this.sizes.length; i++) 
    {
      let angle = (this.sizes[i] / total) * TWO_PI;
      fill(this.colors[i]);
      stroke(0);
      strokeWeight(1);
      arc(width / 2, height / 2, 200, 200, lastAngle, lastAngle + angle, PIE);

      let midAngle = lastAngle + angle / 2;
      let labelX = width / 2 + cos(midAngle) * 130;
      let labelY = height / 2 + sin(midAngle) * 130;

      textSize(17);
      fill(0);
      stroke(this.colors[i]);
      strokeWeight(1.5);
      let percentage = ((this.sizes[i] / total) * 100).toFixed(1);
      text(`${this.labels[i]}: ${percentage}%`, labelX, labelY);

      lastAngle += angle;
    }
  }
}

class Barchart 
{
  constructor(dict, recommended) 
  {
    this.dict = dict;
    this.labels = Object.keys(dict);
    this.sizes = this.calculateSizes();
    this.recommended = recommended;
  }

  convertMgKgToKgHectar()
  {
    for (let i = 0; i < this.sizes.length; i++) 
    {
      let avgValue = ((this.sizes[i]) * 10000 * 25);
    }
  }

  calculateSizes() 
  {
    let sizes = [];
    for (let key in this.dict) 
    {
      let values = this.dict[key];
      let avg = values.reduce((a, b) => a + b, 0) / values.length;
      sizes.push(avg);
    }
    return sizes;
  }

  display() 
  {
    let barWidth = width / this.sizes.length;
    let maxVal = Math.max(...this.sizes, ...Object.values(this.recommended).flat());

    for (let i = 0; i < this.sizes.length; i++) 
    {
      let avgValue = this.sizes[i];
      let recommendedMin = this.recommended[this.labels[i]][0];
      let recommendedMax = this.recommended[this.labels[i]][1];

      let avgBarHeight = map(avgValue, 0, maxVal, 0, height - 50);
      let recMinHeight = map(recommendedMin, 0, maxVal, 0, height - 50);
      let recMaxHeight = map(recommendedMax, 0, maxVal, 0, height - 50);

      fill(100, 150, 200);
      rect(i * barWidth, height - avgBarHeight, barWidth - 10, avgBarHeight);

      fill(150, 200, 100, 150);
      rect(i * barWidth, height - recMaxHeight, barWidth - 10, recMaxHeight - recMinHeight);

      stroke(255, 0, 0);
      strokeWeight(2);
      line(i * barWidth, height - recMinHeight, i * barWidth + barWidth - 10, height - recMinHeight);

      noStroke();
      fill(0);
      textSize(12);
      textAlign(CENTER);
      text(this.labels[i], i * barWidth + barWidth / 2, height - 5);

      textSize(10);
      text(`${avgValue.toFixed(1)} mg/kg`, i * barWidth + barWidth / 2, height - avgBarHeight - 10);
      text(`${recommendedMin.toFixed(1)} kg/ha`, i * barWidth + barWidth / 2, height - recMinHeight - 10);
      text(`${recommendedMax.toFixed(1)} kg/ha`, i * barWidth + barWidth / 2, height - recMaxHeight - 10);
    }
  }
}




