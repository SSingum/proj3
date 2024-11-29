import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css';
import Dropdown from 'react-bootstrap/Dropdown';
import DropdownButton from 'react-bootstrap/DropdownButton';
import logo from './Hash.webp';
import React from 'react';

const labelInput = {
  fontFamily: '"Jersey 10", sans-serif',
  fontSize: "20px",
  color: "#FFFFFF",
  letterSpacing: "3px",
};

const visualizeMinHeap = (arr, index = 0, position = 0, level = 0) => {
  // if min heap empty, return nothing
  if(index >= arr.length){
    return null;
  }

  // get positions for children of current node
  const left = (2 * index) + 1;
  const right = (2 * index) + 2;

  const spacing = 200 / (level + 1);

  return (
    // display current node
    <div>
      <div style={{ position: 'relative', marginLeft: position}}>
        <div
          style={{
            width: 50,
            height: 50,
            backgroundColor: '#FFFFFF',
            color: 'black',
            textAlign: 'center',
            lineHeight: '50px',
            borderRadius: '50%',
          }}>
          {arr[index]}
        </div>
      </div>

      {/* display children nodes recursively*/}
      <div style={{ display: 'flex' }}>
        {visualizeMinHeap(arr, left, position - spacing, level + 1)}
        {visualizeMinHeap(arr, right, position + spacing, level + 1)}
      </div>
    </div>
  );
};

function App() {

  const arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14];
  
  return (
    <div className="App">
      <header className="App-header">

        {/*project image*/}
        <img src={logo} className="App-logo" alt="logo" />

        {/*title*/}
        <p>
          Financial Trend Analyzer
        </p>

        {/*dropdown menu info and functionality from https://react-bootstrap.netlify.app/docs/components/dropdowns/*/}
        <DropdownButton id="dropdown-basic-button" title="Select from options below">
          <Dropdown.Item>
            Option 1
          </Dropdown.Item>
          <Dropdown.Item>
            Option 2
          </Dropdown.Item>
          <Dropdown.Item>
            Option 3
          </Dropdown.Item>
        </DropdownButton>

        <div style={{marginTop: '50px'}}>
          {visualizeMinHeap(arr)}
        </div>

      </header>
    </div>
  );
}

export default App;
